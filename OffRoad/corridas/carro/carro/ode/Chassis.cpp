#include "Chassis.h"
#include "ChassisGeometry.h"
#include "World.h"

/// Cria um novo chassis em world com mass, width, height e length.
Chassis::Chassis(World &world, double mass, double width, double height, double length)
{
	dMass m;

	Object::Init(world, mass);
	this->mass = mass;
	dMassSetBoxTotal(&m, (dReal) mass, (dReal) width, (dReal) length, (dReal) height);
	dBodySetMass(this->body, &m);
	this->geometry = new ChassisGeometry(*(world.WorldSpace()), width, height, length, Geometry::Red);
	dGeomSetBody(this->geometry->ID(), this->body);
}



/// Destrói o chassis.
Chassis::~Chassis()
{
}