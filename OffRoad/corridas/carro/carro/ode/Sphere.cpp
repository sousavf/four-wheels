#include "Sphere.h"
#include "SphereGeometry.h"
#include "World.h"

/// Cria uma esfera com massa e raio específicos.
Sphere::Sphere(World &world, double mass, double radius)
{
	Init(world, mass, radius, false);
}



/// Cria uma esfera com mass, raio e a propriedade bounce específicos. 
Sphere::Sphere(World &world, double mass, double radius, bool bounce)
{
	Init(world, mass, radius, bounce);
}



/// Define as características da esfera.
void Sphere::Init(World &world, double mass, double radius, bool bounce)
{
	dMass m;

	Object::Init(world, mass);
	this->mass = mass;
	dMassSetSphere(&m, (dReal) mass, (dReal) radius);
	this->geometry = new SphereGeometry(*(world.WorldSpace()), radius);
	this->bounce = bounce;
	dGeomSetBody(this->geometry->ID(), this->body);
	dBodySetMass(this->body, &m);
	world.WorldSpace()->AddObject(*this);
}



/// Destrói a esfera.
Sphere::~Sphere()
{
}