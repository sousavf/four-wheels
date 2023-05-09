#include "ODEHeaders.h"

using namespace ODE;

/// Inicia uma nova massa.
ODEMass::ODEMass()
{
	dMassSetZero(&(this->mass));
}



/// Destroi a massa.
ODEMass::~ODEMass()
{
}



/// Devolve o valor da massa.
ODEReal ODEMass::getValue() const
{
	return (ODEReal)this->mass.mass;
}



/// Devolve a massa.
dMass ODEMass::getMass() const
{
	return this->mass;
}



/// Iguala uma massa a outra.
ODEMass& ODEMass::operator = (const ODEMass &m)
{
	this->mass = m.getMass();

	return *this;
}



/// Iguala a massa a uma massa dMass.
ODEMass& ODEMass::operator = (const dMass &m)
{
	this->mass = m;

	return *this;
}