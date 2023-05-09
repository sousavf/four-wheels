#ifndef ODEPLANEGEOMETRY_H
#define ODEPLANEGEOMETRY_H

#include "ODERequirements.h"

namespace ODE
{
	/// Representa a geometria de um plano.
	class ODEPlaneGeometry : public ODEGeometry
	{
	public:
		ODEPlaneGeometry(ODEWorld &world, const ODESpace &space, const ODEVector4 &p);
		~ODEPlaneGeometry();

		void setParams(const ODEVector4 &p);
		void setPosition(const ODEVector3 &pos);
		void setRotation(const ODEMatrix3 &rot);
		void setQuaternion(const ODEQuaternion &orientation);

		const ODEVector4 getParams() const;
		const ODEVector3 getPosition() const;
		const ODEQuaternion getQuaternion() const;
		const ODEMatrix3 getRotation() const;
	};
}

#endif