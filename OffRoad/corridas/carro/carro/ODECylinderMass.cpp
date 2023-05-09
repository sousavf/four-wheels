#include "ODEHeaders.h"

using namespace ODE;

/// Cria uma massa vazia.
ODECylinderMass::ODECylinderMass():ODEMass()
{
}



/// Cria uma massa de um cilindro com os parâmetros específicos.
ODECylinderMass::ODECylinderMass(ODEReal mass, ODEDirection direction, ODEReal radius, ODEReal length)
{
	dMassSetCylinderTotal(&(this->mass), (dReal)mass, (int)direction
		, (dReal)radius, (dReal)length); 
}



/// Destrói a massa.
ODECylinderMass::~ODECylinderMass()
{
}



/// Define os parâmetros da densidade do cilindro.
void ODECylinderMass::setDensity(ODEReal mass, ODEDirection direction, ODEReal radius, ODEReal length)
{
	dMassSetCylinder(&(this->mass), (dReal)mass, (int)direction
		, (dReal)radius, (dReal)length);
}