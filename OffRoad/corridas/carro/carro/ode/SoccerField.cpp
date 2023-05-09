#include "SoccerField.h"
#include "World.h"

/// Cria um novo campo com tamanhos oficiais.
SoccerField::SoccerField(World &world)
{
	Init(world, 64, 100, 7.32, 1, 2.44, XYZ(0, 0, 0));
}



/// Cria um novo campo com tamanhos oficiais e em position.
SoccerField::SoccerField(World &world, XYZ position)
{
	Init(world, 64, 100, 7.32, 1, 2.44, position);
}



/// Constrói um campo de futebol com as dimensões oficiais multiplicadas por multiplier.
SoccerField::SoccerField(World &world, double multiplier)
{
	Init(world, 64 * multiplier, 100 * multiplier, 7.32 * multiplier, 1, 2.44 * multiplier, XYZ(0, 0, 0));
}



/// Constrói um campo de futebol com as dimensões oficiais multiplicadas por multiplier e em position.
SoccerField::SoccerField(World &world, double multiplier, XYZ position)
{
	Init(world, 64 * multiplier, 100 * multiplier, 7.32 * multiplier, 1, 2.44 * multiplier, position);
}



/// Cria uma baliza com as dimensões específicas.
SoccerField::SoccerField(World &world, double width, double length, double netLength)
{
	Init(world, width, length, netLength, width * 0.01, width * 0.1, XYZ(0, 0, 0));
}
 

/// Cria uma baliza com as dimensões e posição específica.
SoccerField::SoccerField(World &world, double width, double length, double netLength, XYZ position)
{
	Init(world, width, length, netLength, width * 0.01, width * 0.05, position);
}
 

/// Cria uma baliza com as dimensões específicas.
SoccerField::SoccerField(World &world, double width, double length, double netLength, double divWidth
		, double divHeight)
{
	Init(world, width, length, netLength, divWidth, divHeight, XYZ(0, 0, 0));
}
 

/// Cria uma baliza com as dimensões e posição específica.
SoccerField::SoccerField(World &world, double width, double length, double netLength, double divWidth
		, double divHeight, XYZ position)
{
	Init(world, width, length, netLength, divWidth, divHeight, position);
}
 

/// Cria uma baliza com as dimensões e posição específica.
void SoccerField::Init(World &world, double width, double length, double netLength, double divWidth
		, double divHeight, XYZ position)
{
	double netOffset, netSideWidth, netSideOffset, sideOffset;
	this->space = new Space(*world.WorldSpace());
	this->geometries = new BoxGeometry*[N_GEOMS];

	for (int i = 0; i < N_GEOMS; i++)
	{
		this->geometries[i] = new BoxGeometry();
	}
	netOffset = length * 0.5 + divWidth * 0.5;
	netSideWidth = (width - netLength) * 0.5;
	netSideOffset = netLength * 0.5 + netSideWidth * 0.5;
	sideOffset = width * 0.5 + divWidth * 0.5;
	this->position = position;

	// partes laterais
	this->geometries[SIDE1]->Init(*(this->space), divWidth, divHeight, length + 2 * divWidth, Geometry::Green);
	this->geometries[SIDE1]->SetPosition(XYZ(position.x + sideOffset, position.y, position.z));
	this->geometries[SIDE2]->Init(*(this->space), divWidth, divHeight, length + 2 * divWidth, Geometry::Green);
	this->geometries[SIDE2]->SetPosition(XYZ(position.x - sideOffset, position.y, position.z));
	

	// balizas
	this->geometries[NET1]->Init(*(this->space), netLength, divHeight, divWidth, Geometry::White);
	this->geometries[NET1]->SetPosition(XYZ(position.x, position.y - netOffset - divWidth, position.z));
	this->geometries[NET2]->Init(*(this->space), netLength, divHeight, divWidth, Geometry::White);
	this->geometries[NET2]->SetPosition(XYZ(position.x, position.y + netOffset + divWidth, position.z));

	// lados balizas
	this->geometries[4]->Init(*(this->space), netSideWidth, divHeight, divWidth, Geometry::Green);
	this->geometries[4]->SetPosition(XYZ(position.x + netSideOffset, position.y - netOffset, position.z));
	this->geometries[5]->Init(*(this->space), netSideWidth, divHeight, divWidth, Geometry::Green);
	this->geometries[5]->SetPosition(XYZ(position.x - netSideOffset, position.y - netOffset, position.z));
	this->geometries[6]->Init(*(this->space), netSideWidth, divHeight, divWidth, Geometry::Green);
	this->geometries[6]->SetPosition(XYZ(position.x + netSideOffset, position.y + netOffset, position.z));
	this->geometries[7]->Init(*(this->space), netSideWidth, divHeight, divWidth, Geometry::Green);
	this->geometries[7]->SetPosition(XYZ(position.x - netSideOffset, position.y + netOffset, position.z));

	// adiciona geometrias ao espaço
	for (int i = 0; i < N_GEOMS; i++)
	{
		this->space->AddGeometry(*(this->geometries[i]));
	}
	world.AddSpace(*(this->space));

	this->width = width;
	this->length = length;
	this->netLength = netLength;
	this->divWidth = divWidth;
	this->divHeight = divHeight;
	this->score[NET1] = 0;
	this->score[NET2] = 0;
}
 

/// Destrói o campo.
SoccerField::~SoccerField()
{
	for (int i = 0; i < N_GEOMS; i++)
	{
		this->geometries[i]->~BoxGeometry();
	}
	this->space->~Space();
	this->position.~XYZ();
	delete this->geometries;
}
 

/// Devolve a largura do campo.
double SoccerField::GetWidth() const
{
	return this->width;
}
 

/// Devolve o comprimento do campo.
double SoccerField::GetLength() const
{
	return this->length;
}
 

/// Devolve o comprimento da baliza.
double SoccerField::GetNetLength() const
{
	return this->netLength;
}
 

/// Devolve o comprimento das paredes.
double SoccerField::GetDivWidth() const
{
	return this->divWidth;
}
 

/// Devolve a altura das paredes.
double SoccerField::GetDivHeight() const
{
	return this->divHeight;
}
 

/// Devolve o espaço onde está inserido o campo.
Space* SoccerField::GetSpace() const
{
	return this->space;
}
 

/// Define a categoria do campo.
void SoccerField::SetCategory(long bits)
{
	for (int i = 0; i < N_GEOMS; i++)
	{
        this->geometries[i]->SetCategory(bits);
	}
}
 

/// Define com o que é que colide o campo.
void SoccerField::SetCollide(long bits)
{
	for (int i = 0; i < N_GEOMS; i++)
	{
        this->geometries[i]->SetCollide(bits);
	}
}



/// Indica se a baliza 1 foi tocada.
bool SoccerField::Net1WasTouched() const
{
	return this->geometries[NET1]->WasTouched();
}



/// Indica se a baliza 2 foi tocada.
bool SoccerField::Net2WasTouched() const
{
	return this->geometries[NET2]->WasTouched();
}



/// Indica se a baliza 1 tocou em object.
bool SoccerField::Net1Touched(Object& object) const
{
	return this->geometries[NET1]->Touched(object);
}



/// Indica se a baliza 1 tocou em geometry.
bool SoccerField::Net1Touched(Geometry& geometry) const
{
	return this->geometries[NET1]->Touched(geometry);
}



/// Indica se a baliza 2 tocou em object.
bool SoccerField::Net2Touched(Object& object) const
{
	return this->geometries[NET2]->Touched(object);
}



/// Indica se a baliza 2 tocou em geometry.
bool SoccerField::Net2Touched(Geometry& geometry) const
{
	return this->geometries[NET2]->Touched(geometry);
}



/// Incrementa os golos que foram marcados na baliza 1.
void SoccerField::IncNet1Score()
{
	this->score[NET1]++;
}



/// Incrementa os golos que foram marcados na baliza 2.
void SoccerField::IncNet2Score()
{
	this->score[NET2]++;
}



/// Indica quandos golos foram marcados na baliza 1.
int SoccerField::Net1Score() const
{
	return this->score[NET1];
}



/// Indica quandos golos foram marcados na baliza 2.
int SoccerField::Net2Score() const
{
	return this->score[NET2];
}



/// Devolve a baliza 1.
BoxGeometry* SoccerField::GetNet1() const
{
	return this->geometries[NET1];
}



/// Devolve a baliza 2.
BoxGeometry* SoccerField::GetNet2() const
{
	return this->geometries[NET2];
}



/// Devolve a posição do campo.
XYZ& SoccerField::GetPosition()
{
	return this->position;
}