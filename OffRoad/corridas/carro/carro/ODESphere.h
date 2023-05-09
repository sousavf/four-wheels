#ifndef ODESPHERE_H
#define ODESPHERE_H

#include "ODERequirements.h"

namespace ODE
{
	/// Representa uma caixa.
	class ODESphere : public ODESimpleObject
	{
	public:
		ODESphere(ODEWorld &world, const ODESpace &space, ODEReal mass, ODEReal radius
			, const ODEContactDefinition &contactDef = ODEContactDefinition());
		~ODESphere();

		void setRadius(ODEReal radius);
		void setMass(ODEReal mass);

		ODEReal getRadius() const;
	};
}

#endif