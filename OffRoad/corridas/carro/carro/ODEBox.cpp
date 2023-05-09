#include "ODEHeaders.h"

using namespace ODE;

/// Constrói uma caixa pertence a world e no espaço space, com as dimensões size e mass.
ODEBox::ODEBox(ODEWorld &world, const ODESpace &space, ODEReal mass
		   , const ODEVector3 &size, const ODEContactDefinition &contactDef)
		   :ODESimpleObject(world)
{
	this->body.setMass(ODEBoxMass(mass, size));
	this->geometry = new ODEBoxGeometry(world, space, size, contactDef);
	this->geometry->setBody(this->body);
}



/// Destrói a caixa.
ODEBox::~ODEBox()
{
}



/// Define as dimensões da caixa.
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



/// Devolve as dimensões da caixa.
const ODEVector3 ODEBox::getSize() const
{
	return ((ODEBoxGeometry*)this->geometry)->getSize();
}