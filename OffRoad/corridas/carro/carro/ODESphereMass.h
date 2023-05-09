#ifndef ODESPHEREMASS_H
#define ODESPHEREMASS_H

#include "ODERequirements.h"

namespace ODE
{
	/// Representa a massa de uma esfera.
	class ODESphereMass : public ODEMass
	{
	public:
		ODESphereMass();
		ODESphereMass(ODEReal mass, ODEReal radius);
		~ODESphereMass();

		void setDensity(ODEReal mass, ODEReal radius);
	};
}

#endif