#include "ODEHeaders.h"

using namespace ODE;

/// Constr�i uma caixa pertence a world e no espa�o space, com as dimens�es size e mass.
ODEBox::ODEBox(ODEWorld &world, const ODESpace &space, ODEReal mass
		   , const ODEVector3 &size, const ODEContactDefinition &contactDef)
		   :ODESimpleObject(world)
{
	this->body.setMass(ODEBoxMass(mass, size));
	this->geometry = new ODEBoxGeometry(world, space, size, contactDef);
	this->geometry->setBody(this->body);
}



/// Destr�i a caixa.
ODEBox::~ODEBox()
{
}



/// Define as dimens�es da caixa.
void ODEBox::setSize(const ODEVector3 &size)
{
	ODEReal mass;

	mass = this->body.getMass().getValue();
	this->body.setMass(ODEBoxMass(mass, size));
	((ODEBoxGeometry*)this->geometry)->setSize(size);
}



/// Define a massa da caixa.
void ODEBox::setMass(ODEReal mass)
{
	ODEVector3 size;

	size = ((ODEBoxGeometry*)this->geometry)->getSize();
	this->body.setMass(ODEBoxMass(mass, size));
}



/// Devolve as dimens�es da caixa.
const ODEVector3 ODEBox::getSize() const
{
	return ((ODEBoxGeometry*)this->geometry)->getSize();
}