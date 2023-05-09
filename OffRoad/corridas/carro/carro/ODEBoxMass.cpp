#include "ODEHeaders.h"

using namespace ODE;

/// Cria uma massa vazia.
ODEBoxMass::ODEBoxMass():ODEMass()
{
}



/// Cria uma massa com massa espec�fica e para as dimens�es size.
ODEBoxMass::ODEBoxMass(ODEReal mass, const ODEVector3 &size)
{
	ODEVector3 size2(size);

	dMassSetBoxTotal(&(this->mass), (dReal)mass, (dReal)size2[0], (dReal)size2[1], (dReal)size2[2]);
}



/// Destr�i a massa.
ODEBoxMass::~ODEBoxMass()
{
}



/// Define a densidade da massa.
void ODEBoxMass::setDensity(ODEReal mass, const ODEVector3 &size)
{
	ODEVector3 size2(size);

	dMassSetBox(&(this->mass), (dReal)mass, (dReal)size2[0], (dReal)size2[1], (dReal)size2[2]);
}