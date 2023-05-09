#ifndef ODECYLINDERGEOMETRY_H
#define ODECYLINDERGEOMETRY_H

#include "ODERequirements.h"

namespace ODE
{
	/// Representa a geometria de uma esfera.
	class ODECylinderGeometry : public ODEGeometry
	{
	public:
		ODECylinderGeometry(ODEWorld &world, const ODESpace &space, ODEReal radius, ODEReal length
			, const ODEContactDefinition &contactDef = ODEContactDefinition());
		~ODECylinderGeometry();

		void setRadius(ODEReal radius);
		void setLength(ODEReal length);
		
		ODEReal getRadius() const;
		ODEReal getLength() const;
	};
}

#endif