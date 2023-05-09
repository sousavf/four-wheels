#include "Race.h"
#include "Utilities.h"
#include "obstaculos/bidon.h"
#include "obstaculos/caixa.h"

Race *Race::handler = NULL;



/// Constrói uma corrida a partir da pista em trackFilename.
Race::Race(ODESimulation &world, const char* trackFilename
		   , vector< ODECar* > &carsODE, vector< veiculo* > &carsGL
		   , vector< ObstacleType > obstacleTypes, int laps)
	:trackODE(world, trackFilename)
{
	this->cenary = new cenario(&this->trackODE);
	this->carsODE = carsODE;
	this->carsGL = carsGL;

	for (int i = 0; i < (int)carsODE.size(); i++)
	{
		this->counters.push_back(LapCounter());
	}
	Init(world, obstacleTypes, laps);
}



/// Constrói uma corrida a partir da pista em trackFilename com nObstacles obstáculos do tipo obstacleType.
Race::Race(ODESimulation &world, const char* trackFilename
		, vector< ODECar* > &carsODE, vector< veiculo* > &carsGL
		, int nObstacles, ObstacleType obstacleType, int laps)
	:trackODE(world, trackFilename)
{
	vector< ObstacleType > obstacleTypes;

	this->cenary = new cenario(&this->trackODE);

	this->carsODE = carsODE;
	this->carsGL = carsGL;

	for (int i = 0; i < (int)carsODE.size(); i++)
	{
		this->counters.push_back(LapCounter());
	}
	
	for (int i = 0; i < nObstacles; i++)
	{
		obstacleTypes.push_back(obstacleType);
	}
	Init(world, obstacleTypes, laps);
}



/// Cria uma nova corrida para um carro.
Race::Race(ODESimulation &world, const char* trackFilename
		, ODECar *carODE, veiculo *carGL, vector< ObstacleType > obstacleTypes
		, int laps)
	:trackODE(world, trackFilename)
{
	this->cenary = new cenario(&this->trackODE);
	this->carsODE.push_back(carODE);
	this->carsGL.push_back(carGL);
	this->counters.push_back(LapCounter());
	Init(world, obstacleTypes, laps);
}



/// Cria uma nova corrida para um carro com nObstacles obstáculos do tipo obstacleType.
Race::Race(ODESimulation &world, const char* trackFilename
		, ODECar *carODE, veiculo *carGL, int nObstacles, ObstacleType obstacleType
		, int laps)
	:trackODE(world, trackFilename)
{
	this->cenary = new cenario(&this->trackODE);
	vector< ObstacleType > obstacleTypes;

	this->carsODE.push_back(carODE);
	this->carsGL.push_back(carGL);
	this->counters.push_back(LapCounter());

	for (int i = 0; i < nObstacles; i++)
	{
		obstacleTypes.push_back(obstacleType);
	}
	Init(world, obstacleTypes, laps);
}



/// Inicia uma nova pista.
void Race::Init(ODESimulation &world, vector< ObstacleType > obstacleTypes, int laps)
{
	ODEVector3 segSize, segPosition, position;
	ODEReal sizeX, sizeY;
	int x, y;
	bool **preenchido = new bool*[this->trackODE.getLength()];

	this->world = &world;
	this->laps = laps;
	this->ended = false;
	handler = this;

	if ((int)obstacleTypes.size() <= 0)
	{
		return;
	}

	for (int i = 0; i < this->trackODE.getLength(); i++)
	{
		preenchido[i] = new bool[this->trackODE.getWidth()];

		for (int j = 0; j < this->trackODE.getWidth(); j++)
		{
			preenchido[i][j] = false;
		}
	}

	for (int i = 0; (i < (int)obstacleTypes.size())
		&& (i < (int)(this->trackODE.getWidth() * this->trackODE.getLength())); i++)
	{
		x = Utilities::Random(0, this->trackODE.getWidth());
		y = Utilities::Random(0, this->trackODE.getLength());

		if (preenchido[y][x]
				|| (this->trackODE.getSegment(x, y).getType() == ODETrackSegmentDefinition::Empty)
				|| ODETrackValidator::start(this->trackODE.getSegment(x, y).getType()) )
		{
			i--;
			continue;
		}
		preenchido[y][x] = true;
		segSize = this->trackODE.getSegment(x, y).getSize();
		segPosition = this->trackODE.getSegment(x, y).getPosition();
		sizeX = 0.4f * segSize[0];
		sizeY = 0.4f * segSize[1];
		position[0] = segPosition[0] + Utilities::Random(-sizeX, sizeX);
		position[1] = segPosition[1] + Utilities::Random(-sizeY, sizeY);
		position[2] = segPosition[2] + 0.5 * this->trackODE.getSegment(x, y).getBorderSize();
		this->obstaclesODE.push_back(newObstacleODE(obstacleTypes[i], position));
		this->world->addObject(this->obstaclesODE[i]);
		this->obstaclesGL.push_back(newObstacleGL(obstacleTypes[i]));
	}

	for (int i = 0; i < this->trackODE.getLength(); i++)
	{
		delete[] preenchido[i];
	}
	delete[] preenchido;
}



/// Cria e devolve um objecto ODE correspondente a type na posição pos.
ODESimpleObject * Race::newObstacleODE(ObstacleType type, ODEVector3 &pos)
{
	ODESimpleObject *object;
	ODEReal height;

	switch (type)
	{
	case Barrel:
		height = 1.2f;
		object = new ODECylinder(*this->world, this->world->getSpace()
			, 1.0f, 0.6f, height
			, ODEContactDefinition(2.5f, -1, -1, -1, -1, -1, -1, -1, -1, -1));
		break;

	case StrawBales:
		height = 0.8f;
		object = new ODEBox(*this->world, this->world->getSpace()
			, 0.1f, ODEVector3(2.0f, 0.7f, height)
			, ODEContactDefinition(2.5f, -1, -1, -1, -1, -1, -1, -1, -1, -1));
		break;

	case WoodBox:
	default:
		height = 1.5f;
		object = new ODEBox(*this->world, this->world->getSpace(), 1.0f
			, ODEVector3(1.5f, 1.5f, height)
			, ODEContactDefinition(2.5f, -1, -1, -1, -1, -1, -1, -1, -1, -1));
		break;
	}
	pos[2] += height * 0.5f;
	object->setPosition(pos);

	return object;
}



/// Cria e devolve um objecto gráfico correspondente a type.
objecto * Race::newObstacleGL(ObstacleType type)
{
	switch (type)
	{
	case Barrel:
		return new bidon(1.2f, 0.6f);

	case StrawBales:
		return new caixa("texturas/obstaculos/fardo/", 2.0f, 0.7f, 0.8f);

	case WoodBox:
	default:
		return new caixa("texturas/obstaculos/caixa/", 1.5f, 1.5f, 1.5f);
	}
}



/// Destrói a corrida.
Race::~Race()
{
	handler = NULL;

	for (int i = 0; i < (int)this->carsODE.size(); i++)
	{
		this->world->removeObject(this->carsODE[i]);
		this->carsODE[i]->~ODECar();
		this->carsGL[i]->~veiculo();
	}

	for (int i = 0; i < (int)this->obstaclesODE.size(); i++)
	{
		this->world->removeObject(this->obstaclesODE[i]);
		this->obstaclesODE[i]->~ODESimpleObject();
		//this->obstaclesGL[i]->~object();
	}

	this->cenary->~cenario();
}



/// Começa a corrida e devolve True se teve sucesso ou false
/// se não foi possível (se a pista estiver inválida).
bool Race::start()
{
	if (!this->trackODE.isValid())
	{
		return false;
	}
	this->world->setCreateContact(&createContactHandler);
	this->trackGL.CarregaPista(this->trackODE);

	for (int i = 0; i < (int)this->carsODE.size(); i++)
	{
		this->counters[i].start();
		this->trackODE.setStart(0, (int)this->carsODE.size(), *this->carsODE[i]);

		for (int i = 0; i < (int)carsODE.size(); i++)
		{
			this->world->addObject(carsODE[i]);
		}
	}

	return true;
}



/// Indica se a corrida já terminou.
bool Race::hasEnded() const
{
	return this->ended;
}



/// Desenha a pista e os carros.
void Race::draw()
{
	this->cenary->desenha();

	this->trackGL.desenha();

	for (int i = 0; i < (int)this->carsODE.size(); i++)
	{
		drawCar(i);
	}

	for (int i = 0; i < (int)this->obstaclesODE.size(); i++)
	{
		drawObstacle(i);
	}
}



/// Desenha o carro correspondente a index. True se o carro existir
/// ou false em contrário.
bool Race::drawCar(int index)
{
	if ( (index < 0) || (index >= (int)this->carsODE.size()) )
	{
		return false;
	}
	ODEVector3 position, rotationAngles;

	position = this->carsODE[index]->getPosition();
	rotationAngles = this->carsODE[index]->getQuaternion().getEulerAngles();
	this->carsGL[index]->translacao(position[1], -position[0], position[2]);
	this->carsGL[index]->rotacao(rotationAngles[1], 180 + rotationAngles[0], rotationAngles[2]);
	this->carsGL[index]->desenha();

	return true;
}



/// Desenha o obstáculo correspondente a index. True se o carro existir
/// ou false em contrário.
bool Race::drawObstacle(int index)
{
	if ( (index < 0) || (index >= (int)this->obstaclesODE.size()) )
	{
		return false;
	}
	ODEVector3 position, rotationAngles;

	position = this->obstaclesODE[index]->getPosition();
	rotationAngles = this->obstaclesODE[index]->getQuaternion().getEulerAngles();
	this->obstaclesGL[index]->translacao(position[1], -position[0], position[2]);
	//this->obstaclesGL[index]->rotacao(rotationAngles[0], rotationAngles[2], rotationAngles[1]);
	this->obstaclesGL[index]->rotacao(rotationAngles[1], 180 + rotationAngles[0], rotationAngles[2]);
	this->obstaclesGL[index]->desenha();

	return true;
}



/// Devolve os contadores com as voltas e tempos de cada carro.
vector< LapCounter > & Race::getCounters()
{
	return this->counters;
}



/// Devolve o contador correspondente a index.
const LapCounter & Race::getCounter(int index) const
{
	return this->counters[index];
}



/// Devolve os carros ODE.
const vector< ODECar* > & Race::getCarsODE() const
{
	return this->carsODE;
}



/// Devolve o carro ODE correspondente a index.
const ODECar & Race::getCarODE(int index) const
{
	return *this->carsODE[index];
}



/// Versão não constante do método acima.
ODECar & Race::getCarODE(int index)
{
	return *this->carsODE[index];
}

veiculo & Race::getCarGL(int index)
{
	return *this->carsGL[index];
}

/// Devolve a roda associada a geom ou NULL se não a encontrar.
ODEWheel* Race::getWheel(ODEGeometry* geom1, ODEGeometry* geom2)
{
	ODEWheel *wheel;

	for (int i = 0; i < (int)this->carsODE.size(); i++)
	{
		for (int j = 0; j < 4; j++)
		{
			wheel = &(this->carsODE[i]->getWheelAt((ODEWheel::Position)j));

			if (wheel->isAnyOf(geom1, geom2))
			{
				return wheel;
			}
		}
	}

	return NULL;
}



/// Devolve o nr. de carros na corrida.
int Race::count() const
{
	return (int)this->counters.size();
}



/// Devolve o nr. de voltas da corrida.
int Race::getLaps() const
{
	return this->laps;
}



/// Devolve a parte da pista do ODE.
const ODETrack & Race::getTrackODE() const
{
	return this->trackODE;
}



/// Trata das colisões.
bool Race::createContact(ODEContact& contact, ODEGeometry* geom1, ODEGeometry* geom2)
{
	if (this->trackODE.startLineIsAnyOf(geom1, geom2))
	{
		int i = carTouchedStartLine(geom1, geom2);

		if (i >= 0)
		{
			this->counters[i].incLaps();

			if (this->counters[i].getLaps() >= this->laps)
			{
				this->ended = true;
			}
			//printf("%d\t%d\n", this->counters[i].getLaps(), this->counters[i].getLastTime());
		}

		return false;
	}
	contact.setFrictionMode(ODEContact::BothFrictionPyramids);
	contact.setParameters(geom1->getContactDefinition(), geom2->getContactDefinition());

	if (geom1->hasBody() || geom2->hasBody())
	{
		ODEWheel *wheel = getWheel(geom1, geom2);

		if (wheel != NULL)
		{
			//wheel->applyPerpendicularFDS(contact);
		}
	}

	return true;
}



/// Devolve o índice do carro que tocou a meta (geom1 ou geom2) ou -1
/// se não houver.
int Race::carTouchedStartLine(ODEGeometry* geom1, ODEGeometry* geom2)
{
	for (int i = 0; i < (int)this->carsODE.size(); i++)
	{
		if (this->trackODE.touchedStartLine(*this->carsODE[i], geom1, geom2))
		{
			return i;
		}
	}

	return -1;
}



bool Race::createContactHandler(ODEContact& contact, ODEGeometry* geom1
		, ODEGeometry* geom2)
{
	if (handler != NULL)
	{
		return handler->createContact(contact, geom1, geom2);
	}

	return false;
}