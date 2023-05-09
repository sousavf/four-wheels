#include "Cylinder.h"
#include "CylinderGeometry.h"
#include "World.h"

/// Cria um cilindro com massa e raio espec�ficos.
Cylinder::Cylinder(World &world, double mass, double radius, double length)
{
	Init(world, mass, radius, length);
}



/// Define as caracter�sticas do cilindro.
void Cylinder::Init(World &world, double mass, double radius, double length)
{
	dMass m;

	Object::Init(world, mass);
	this->mass = mass;
	dMassSetCylinder(&m, (dReal) mass, 1, (dReal) radius, (dReal) length);
	this->geometry = new CylinderGeometry(*(world.WorldSpace()), radius, length);
	dGeomSetBody(this->geometry->ID(), this->body);
	dBodySetMass(this->body, &m);
	world.WorldSpace()->AddObject(*this);
}



/// Destr�i a esfera.
Cylinder::~Cylinder()
{
}