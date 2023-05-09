#ifndef ODEMASS_H
#define ODEMASS_H

#include "ODERequirements.h"

namespace ODE
{
	/// Representa uma massa (que deverá pertencer a um corpo).
	/// Existem subclasses específicas para cada tipo de massa (massa de esfera, massa de caixa, ...).
	class ODEMass
	{
	public:
		ODEMass();
		~ODEMass();

		ODEReal getValue() const;
		dMass getMass() const;
		ODEMass& operator = (const ODEMass &m);
		ODEMass& operator = (const dMass &m);

	protected:
		dMass mass;
	};
}

#endif