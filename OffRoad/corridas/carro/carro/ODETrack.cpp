#include "ODEHeaders.h"

using namespace ODE;

/// Constrói a pista.
/// A meta deve sempre corresponder a um troço de pista "horizontal" ou "vertical",
/// senão pode dar problemas...
ODETrack::ODETrack(ODEWorld &world, const string& name
	, ODETrackSegmentDefinition::Surface groundSurface
	, ODETrackSegmentDefinition::Surface sidelinesSurface
	,  vector< vector< ODETrackSegmentDefinition > >& segDefinitions)
	:space(world, world.getSpace())
{
	Init(world, name, groundSurface, sidelinesSurface, segDefinitions);
}



/// Constrói a pista a partir do ficheiro filename.
ODETrack::ODETrack(ODEWorld &world, const char* filename):space(world, world.getSpace())
{
	vector< vector< ODETrackSegmentDefinition > > segments;
	ODETrackSegmentDefinition::Surface ground, sidelines;
	string name;

	Load(filename, name, ground, sidelines, segments);
	Init(world, name, ground, sidelines, segments);
}



/// Constrói a pista.
void ODETrack::Init(ODEWorld &world, const string& name
	, ODETrackSegmentDefinition::Surface groundSurface
	, ODETrackSegmentDefinition::Surface sidelinesSurface
	, vector< vector< ODETrackSegmentDefinition > >& segDefinitions)
{
	ODEVector3 position, startSize, startSegmentPosition[2];
	ODETrackSegment *startSegment;
	int axis, mult;

	this->world = &world;
	this->name = name;
	this->groundSurface = groundSurface;
	this->sidelinesSurface = sidelinesSurface;
	position[2] = (segDefinitions.size() > 0 && segDefinitions[0].size() > 0
		? 0.5f * segDefinitions[0][0].getBorderSize() : 0);

	for (int i = 0; i < (int)segDefinitions.size(); i++)
	{
		this->segments.push_back(vector< ODETrackSegment* >());

		for (int j = 0; j < (int)segDefinitions[i].size(); j++)
		{
			position[0] = (j == 0 ? 0
				: this->segments[i][j - 1]->getPosition()[0]
				+ 0.5f * segDefinitions[i][j - 1].getSize()[0]
				+ 0.5f * segDefinitions[i][j].getSize()[0]);
			position[1] = (i == 0 ? 0
				: this->segments[i - 1][j]->getPosition()[1]
				+ 0.5f * segDefinitions[i - 1][j].getSize()[1]
				+ 0.5f * segDefinitions[i][j].getSize()[1]);
			segDefinitions[i][j].setGroundSurface(this->groundSurface);
			segDefinitions[i][j].setSidelinesSurface(this->sidelinesSurface);
			this->segments[(int)this->segments.size() - 1].push_back(new ODETrackSegment(world, this->space
				, segDefinitions[i][j], position));

			if (segDefinitions[i][j].isStartLine())
			{
				this->startX = j;
				this->startY = i;
				this->startSegment = this->segments[i][j];
			}
		}
	}
	startSegment = this->segments[this->startY][this->startX];
	startSize = startSegment->getSize();

	switch (startSegment->getType())
	{
	case ODETrackSegmentDefinition::StartStraightFront:
		axis = 1;
		mult = -1;
		break;

	case ODETrackSegmentDefinition::StartStraightBack:
		axis = 1;
		mult = 1;
		break;

	case ODETrackSegmentDefinition::StartStraightLeft:
		axis = 0;
		mult = 1;
		break;

	case ODETrackSegmentDefinition::StartStraightRight:
		axis = 0;
		mult = -1;
		break;
	}
	startSize[axis] = startSegment->getBorderSize();
	startSegmentPosition[1] = startSegmentPosition[0] = startSegment->getPosition();
	startSegmentPosition[0][axis] -= mult * 0.5f * startSegment->getGround(0).getSize()[axis];
	startSegmentPosition[1][axis] += mult * 0.5f * startSegment->getGround(0).getSize()[axis];

	for (int i = 0; i < 2; i++)
	{
		this->startLine[i] = new ODEBoxGeometry(world, this->space, startSize);
		this->startLine[i]->setPosition(startSegmentPosition[i]);
	}
	this->startLineTouched[0] = false;
	this->startLineTouched[1] = true;
}



/// Destrói a pista.
ODETrack::~ODETrack()
{
	while (!this->segments.empty())
	{
		while (!this->segments[0].empty())
		{
			this->segments[0][0]->~ODETrackSegment();
			this->segments[0].erase(this->segments[0].begin());
		}
		this->segments.erase(this->segments.begin());
	}
	startLine[0]->~ODEBoxGeometry();
	startLine[1]->~ODEBoxGeometry();
}



/// Devolve o segmento correspondente a x, y.
const ODETrackSegment& ODETrack::getSegment(int x, int y) const
{
	return *(this->segments[y][x]);
}



/// Devolve a geometria que correspondente à meta.
const ODEBoxGeometry& ODETrack::getStartLine() const
{
	return *(this->startLine[1]);
}



/// Devolve a "largura" da pista (número de segmentos em x).
int ODETrack::getWidth() const
{
	return (getLength() > 0 ? (int)this->segments[0].size() : 0);
}



/// Devolve o "comprimento" da pista (número de segmentos em y).
int ODETrack::getLength() const
{
	return (int)this->segments.size();
}



/// Devolve o nome da pista.
const string& ODETrack::getName() const
{
	return this->name;
}



/// Devolve o espaço desta pista.
const ODESpace& ODETrack::getSpace() const
{
	return this->space;
}



/// Indica se a pista é válida.
bool ODETrack::isValid() const
{
	if (this->segments.size() == 0)
	{
		return false;
	}
	vector< vector< ODETrackSegmentDefinition > > segDefinitions;

	for (int i = 0; i < (int)this->segments.size(); i++)
	{
		segDefinitions.push_back(vector< ODETrackSegmentDefinition >());

		for (int j = 0; j < (int)this->segments[i].size(); j++)
		{
			segDefinitions[i].push_back(this->segments[i][j]->getDefinition());
		}
	}
	
	return ODETrackValidator::isValid(segDefinitions);
}



/// Estabelece a posição e rotação inicial do carro correspondente a carPosition.
/// carPosition corresponde à posição do carro na grelha de partida (1º, 2º, 3º... lugar).
///	Neste momento, é indiferente o valor de carPosition, porque assume sempre
/// que só há um carro na corrida, ...
void ODETrack::setStart(int carPosition, int cars, ODECar &car) const
{
	ODEVector3 pos;
	ODEQuaternion rot;
	ODEReal z;

	z = car.getPosition()[2];
	rot = car.getQuaternion();
	pos = this->startSegment->getPosition();
	pos[2] = z;

	switch (this->startSegment->getType())
	{
	case ODETrackSegmentDefinition::StartStraightLeft:
		rot.fromAxisAndAngle(0, 0, 1, 0.5 * M_PI);
		car.setThrottleForce(-car.getThrottleForce());
		break;

	case ODETrackSegmentDefinition::StartStraightRight:
		rot.fromAxisAndAngle(0, 0, 1, -0.5 * M_PI);
		car.setThrottleForce(-car.getThrottleForce());
		break;

	case ODETrackSegmentDefinition::StartStraightBack:
		rot.fromAxisAndAngle(0, 0, 1, 0);
		break;

	default:
	case ODETrackSegmentDefinition::StartStraightFront:
		rot.fromAxisAndAngle(0, 0, 1, M_PI);
		break;
	}
	car.setPosition(pos);
	car.setQuaternion(rot);
}



/// Devolve o segmento onde está a metda.
ODETrackSegment& ODETrack::getStartSegment()
{
	return *(this->startSegment);
}



/// Indica se a direcção em que o carro se dirige e o segmento inicial são coincidentes.
bool ODETrack::areCoincident(const ODETrackSegment &startSegment, ODECar &car)
{
	if ( ((startSegment.getType() == ODETrackSegmentDefinition::StartStraightFront)
			&& (car.getLinearVelocity()[1] > 0))
		|| ((startSegment.getType() == ODETrackSegmentDefinition::StartStraightBack)
			&& (car.getLinearVelocity()[1] < 0))
		|| ((startSegment.getType() == ODETrackSegmentDefinition::StartStraightLeft)
			&& (car.getLinearVelocity()[0] > 0))
		|| ((startSegment.getType() == ODETrackSegmentDefinition::StartStraightRight)
			&& (car.getLinearVelocity()[0] < 0)) )
	{
		return false;
	}

	return true;
}



/// Indica se a meta foi tocada por car.
bool ODETrack::touchedStartLine(ODECar &car, const ODEGeometry &geom1, const ODEGeometry &geom2)
{
	if (!car.isAnyOf(geom1, geom2))
	{
		return false;
	}

	if (this->startLine[0]->isAnyOf(geom1, geom2))
	{
		this->startLineTouched[0] = true;
	}
	else if (this->startLine[1]->isAnyOf(geom1, geom2))
	{
		if (!areCoincident(*(this->startSegment), car))
		{
			this->startLineTouched[1] = true;
		}
		else
		{
			if (this->startLineTouched[1])
			{
				this->startLineTouched[0] = false;
				this->startLineTouched[1] = false;
			}
			else if (this->startLineTouched[0])
			{
				this->startLineTouched[0] = false;

				return true;
			}
		}
	}

	return false;
}



/// Indica se a meta foi tocada por car.
bool ODETrack::touchedStartLine(ODECar &car, const ODEGeometry *geom1, const ODEGeometry *geom2)
{
	return touchedStartLine(car, *geom1, *geom2);
}



/// Indica se a meta é uma das duas geometrias.
bool ODETrack::startLineIsAnyOf(const ODEGeometry &geom1, const ODEGeometry &geom2)
{
	return (this->startLine[0]->isAnyOf(geom1, geom2) || this->startLine[1]->isAnyOf(geom1, geom2));
}



/// Indica se a meta é uma das duas geometrias.
bool ODETrack::startLineIsAnyOf(const ODEGeometry *geom1, const ODEGeometry *geom2)
{
	return startLineIsAnyOf(*geom1, *geom2);
}



/// Carrega a definição de uma pista do ficheiro filename.
bool ODETrack::Load(const char* filename, string &trackName
	, ODETrackSegmentDefinition::Surface &groundSurface
	, ODETrackSegmentDefinition::Surface &sidelinesSurface
	, vector< vector< ODETrackSegmentDefinition > >& segDefinitions)
{
	ODETrackSegmentDefinition seg = ODETrackSegmentDefinition::get(ODETrackSegmentDefinition::Empty);
	int width, length, s;
	char name[1000], c;

	ifstream ifile(filename);

	if (!ifile.is_open())
	{
		return false;
	}
	ifile.getline(name, 1000, ';');
	trackName = name;
	ifile >> length;
	ifile >> c;	// para ignorar ;
	ifile >> width;
	ifile >> c;	// para ignorar ;
	ifile >> s;
	ifile >> c;	// para ignorar ;
	groundSurface = (ODETrackSegmentDefinition::Surface)s;
	ifile >> s;
	ifile >> c;	// para ignorar ;
	sidelinesSurface = (ODETrackSegmentDefinition::Surface)s;
	segDefinitions.clear();
	
	for (int i = 0; i < length; i++)
	{
		segDefinitions.push_back(vector< ODETrackSegmentDefinition >());

		for (int j = 0; j < width; j++)
		{
			ifile >> seg;
			segDefinitions[i].push_back(ODETrackSegmentDefinition(seg));
		}
	}
	ifile.close();

	return true;
}



/// Guarda a definição de uma pista para o ficheiro filename.
void ODETrack::Save(const char* filename, const string &trackName
	, ODETrackSegmentDefinition::Surface groundSurface
	, ODETrackSegmentDefinition::Surface sidelinesSurface
	, const vector< vector< ODETrackSegmentDefinition > >& segDefinitions)
{
	if (segDefinitions.size() <= 0)
	{
		return;
	}
	ofstream ofile(filename);

	ofile << trackName << ";";
	ofile << (int)segDefinitions.size() << ";";
	ofile << (int)segDefinitions[0].size() << ";";
	ofile << (int)groundSurface << ";";
	ofile << (int)sidelinesSurface << ";";
	ofile << endl;
	
	for (int i = 0; i < (int)segDefinitions.size(); i++)
	{
		for (int j = 0; j < (int)segDefinitions[i].size(); j++)
		{
			ofile << segDefinitions[i][j];
		}
		ofile << endl;
	}
	ofile.close();
}



ODETrackSegmentDefinition::Surface ODETrack::getGroundSurface() const
{
	return this->groundSurface;
}



ODETrackSegmentDefinition::Surface ODETrack::getSidelinesSurface() const
{
	return this->sidelinesSurface;
}
