#include "ODEHeaders.h"

using namespace ODE;

/// Cria um cilindro.
ODECylinder::ODECylinder(ODEWorld &world, const ODESpace &space, ODEReal mass
	, ODEReal radius, ODEReal length, const ODEContactDefinition &contactDef)
	:ODESimpleObject(world)
{
	this->body.setMass(ODECylinderMass(mass, ODE::Z, radius, length));
	this->geometry = new ODECylinderGeometry(world, space, radius, length, contactDef);
	this->geometry->setBody(this->body);
}



/// Destrói o cilindro.
ODECylinder::~ODECylinder()
{
}



/// Define a massa do cilindro.
void ODECylinder::setMass(ODEReal mass)
{
	ODEReal radius, length;

	radius = ((ODECylinderGeometry*)this->geometry)->getRadius();
	length = ((ODECylinderGeometry*)this->geometry)->getLength();
	this->body.setMass(ODECylinderMass(mass, ODE::Z, radius, length));
}



/// Define o raio do cilindro.
void ODECylinder::setRadius(ODEReal radius)
{
	ODEReal mass, length;

	mass = this->body.getMass().getValue();
	length = ((ODECylinderGeometry*)this->geometry)->getLength();
	this->body.setMass(ODECylinderMass(mass, ODE::Z, radius, length));
	((ODECylinderGeometry*)this->geometry)->setRadius(radius);

}



/// Define o comprimento do cilindro.
void ODECylinder::setLength(ODEReal length)
{
	ODEReal mass, radius;

	mass = this->body.getMass().getValue();
	radius = ((ODECylinderGeometry*)this->geometry)->getRadius();
	this->body.setMass(ODECylinderMass(mass, ODE::Z, radius, length));
	((ODECylinderGeometry*)this->geometry)->setLength(length);
}



/// Devolve o raio do cilindro.
ODEReal ODECylinder::getRadius() const
{
	return ((ODECylinderGeometry*)this->geometry)->getRadius();
}



/// Devolve o comprimento do cilindro.
ODEReal ODECylinder::getLength() const
{
	return ((ODECylinderGeometry*)this->geometry)->getLength();
}