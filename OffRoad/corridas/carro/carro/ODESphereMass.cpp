#include "ODEHeaders.h"

using namespace ODE;

/// Cria uma massa vazia.
ODESphereMass::ODESphereMass():ODEMass()
{
}



/// Cria uma massa com massa específica e com raio radius.
ODESphereMass::ODESphereMass(ODEReal mass, ODEReal radius)
{
	dMassSetSphereTotal(&(this->mass), (dReal)mass, (dReal)radius);
}



/// Destrói a massa.
ODESphereMass::~ODESphereMass()
{
}



/// Define a densidade da massa.
void ODESphereMass::setDensity(ODEReal mass, ODEReal radius)
{
	dMassSetSphere(&(this->mass), (dReal)mass, (dReal)radius);
}