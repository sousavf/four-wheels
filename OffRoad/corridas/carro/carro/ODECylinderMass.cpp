#include "ODEHeaders.h"

using namespace ODE;

/// Cria uma massa vazia.
ODECylinderMass::ODECylinderMass():ODEMass()
{
}



/// Cria uma massa de um cilindro com os par�metros espec�ficos.
ODECylinderMass::ODECylinderMass(ODEReal mass, ODEDirection direction, ODEReal radius, ODEReal length)
{
	dMassSetCylinderTotal(&(this->mass), (dReal)mass, (int)direction
		, (dReal)radius, (dReal)length); 
}



/// Destr�i a massa.
ODECylinderMass::~ODECylinderMass()
{
}



/// Define os par�metros da densidade do cilindro.
void ODECylinderMass::setDensity(ODEReal mass, ODEDirection direction, ODEReal radius, ODEReal length)
{
	dMassSetCylinder(&(this->mass), (dReal)mass, (int)direction
		, (dReal)radius, (dReal)length);
}