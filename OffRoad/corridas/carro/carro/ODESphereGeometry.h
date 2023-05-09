#ifndef ODESPHEREGEOMETRY_H
#define ODESPHEREGEOMETRY_H

#include "ODERequirements.h"

namespace ODE
{
	/// Representa a geometria de uma esfera.
	class ODESphereGeometry : public ODEGeometry
	{
	public:
		ODESphereGeometry(ODEWorld &world, const ODESpace &space, ODEReal radius
			, const ODEContactDefinition &contactDef = ODEContactDefinition());
		~ODESphereGeometry();

		void setRadius(ODEReal radius);
		ODEReal getRadius() const;
	};
}

#endif