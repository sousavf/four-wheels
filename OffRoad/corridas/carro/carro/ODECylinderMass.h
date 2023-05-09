#ifndef ODECYLINDERMASS_H
#define ODECYLINDERMASS_H

#include "ODERequirements.h"

namespace ODE
{
	/// Representa a massa de um cilindro.
	class ODECylinderMass : public ODEMass
	{
	public:
		ODECylinderMass();
		ODECylinderMass(ODEReal mass, ODEDirection direction, ODEReal radius, ODEReal length);
		~ODECylinderMass();

		void setDensity(ODEReal mass, ODEDirection direction, ODEReal radius, ODEReal length);
	};
}

#endif