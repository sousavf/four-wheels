#ifndef ODEBOXMASS_H
#define ODEBOXMASS_H

#include "ODERequirements.h"

namespace ODE
{
	/// Representa a massa de uma caixa.
	class ODEBoxMass : public ODEMass
	{
	public:
		ODEBoxMass();
		ODEBoxMass(ODEReal mass, const ODEVector3 &size);
		~ODEBoxMass();

		void setDensity(ODEReal mass, const ODEVector3 &size);
	};
}

#endif