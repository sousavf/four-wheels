#include "ODEHeaders.h"

using namespace ODE;

/// Cria uma esfera.
ODESphere::ODESphere(ODEWorld &world, const ODESpace &space, ODEReal mass
		, ODEReal radius, const ODEContactDefinition &contactDef)
		:ODESimpleObject(world)
{
	this->body.setMass(ODESphereMass(mass, radius));
	this->geometry = new ODESphereGeometry(world, space, radius, contactDef);
	this->geometry->setBody(this->body);
}



/// Destrói a esfera.
ODESphere::~ODESphere()
{
}



/// Define o raio da esfera.
void ODESphere::setRadius(ODEReal radius)
{
	ODEReal mass;

	mass = this->body.getMass().getValue();
	this->body.setMass(ODESphereMass(mass, radius));
	((ODESphereGeometry*)this->geometry)->setRadius(radius);
}



/// Define a massa da esfera.
void ODESphere::setMass(ODEReal mass)
{
	ODEReal radius;

	radius = ((ODESphereGeometry*)this->geometry)->getRadius();
	this->body.setMass(ODESphereMass(mass, radius));
}



/// Devolve o raio.
ODEReal ODESphere::getRadius() const
{
	return ((ODESphereGeometry*)this->geometry)->getRadius();
}