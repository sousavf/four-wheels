#ifndef ODEBOXGEOMETRY_H
#define ODEBOXGEOMETRY_H

#include "ODERequirements.h"

namespace ODE
{
	/// Representa a geometria de uma caixa. Para representar cubos, paralelipipedos, ...
	class ODEBoxGeometry : public ODEGeometry
	{
	public:
		ODEBoxGeometry(ODEWorld &world, const ODESpace &space, const ODEVector3 &size
			, const ODEContactDefinition &contactDef = ODEContactDefinition());
		~ODEBoxGeometry();

		void setSize(const ODEVector3 &size);
		const ODEVector3 getSize() const;
	};
}

#endif