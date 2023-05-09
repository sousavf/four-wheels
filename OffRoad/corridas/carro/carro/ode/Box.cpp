#include "Box.h"
#include "BoxGeometry.h"
#include "World.h"

/// Cria uma nova caixa como um cubo com lado size em world com mass.
Box::Box(World &world, double mass, double size)
{
	Init(world, mass, size, size, size, true);
}



/// Cria uma nova caixa com dimens�es width, height, length em world com mass.
Box::Box(World &world, double mass, double width, double height, double length)
{
	Init(world, mass, width, height, length, true);
}



/// Cria uma nova caixa com dimens�es width, height, length em world com mass e adiciona-o ou n�o a World.
Box::Box(World &world, double mass, double width, double height, double length, bool addToWorld)
{
	Init(world, mass, width, height, length, addToWorld);
}



/// Define as caracter�sticas da caixa.
void Box::Init(World &world, double mass, double width, double height, double length, bool addToWorld)
{
	dMass m;

	Object::Init(world, mass);
	this->mass = mass;
	dMassSetBoxTotal(&m, (dReal) mass, (dReal) width, (dReal) length, (dReal) height);
	dBodySetMass(this->body, &m);
	this->geometry = new BoxGeometry(*(world.WorldSpace()), width, height, length);
	dGeomSetBody(this->geometry->ID(), this->body);

	if (addToWorld)
	{
		world.WorldSpace()->AddObject(*this);
	}
}



/// Destr�i a caixa.
Box::~Box()
{
}