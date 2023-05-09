#ifndef ODECYLINDER_H
#define ODECYLINDER_H

#include "ODERequirements.h"

namespace ODE
{
	/// Representa um cilindro.
	class ODECylinder : public ODESimpleObject
	{
	public:
		ODECylinder(ODEWorld &world, const ODESpace &space, ODEReal mass
			, ODEReal radius, ODEReal length
			, const ODEContactDefinition &contactDef = ODEContactDefinition());
		~ODECylinder();

		void setMass(ODEReal mass);
		void setRadius(ODEReal radius);
		void setLength(ODEReal length);
		
		ODEReal getRadius() const;
		ODEReal getLength() const;
	};
}

#endif