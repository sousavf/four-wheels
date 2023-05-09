#ifndef ODEQUATERNION_H
#define ODEVQUATERNION_H

#include "ODERequirements.h"

namespace ODE
{
	/// Representa um vector com 4 posições que normalmente representam
	/// as coordenadas w, x, y, z, que costuma ser usado em rotações, ...
	class ODEQuaternion
	{
	public:
		ODEQuaternion();
		ODEQuaternion(ODEReal w, ODEReal x, ODEReal y, ODEReal z);
		ODEQuaternion(const ODEQuaternion &q);
		~ODEQuaternion();

		void fromAxisAndAngle(ODEReal ax, ODEReal ay, ODEReal az, ODEReal angle);
		const ODEVector3 getEulerAngles() const;

		ODEVector3 operator* (const ODEVector3 &v) const;
		ODEQuaternion& operator = (const dReal *q);
		ODEQuaternion& operator = (const ODEQuaternion &q);
		ODEReal& operator [] (int index);
		ODEReal operator [] (int index) const;
		bool operator == (const ODEQuaternion &q) const;

	protected:
		ODEReal data[4];

		void Init(ODEReal w, ODEReal x, ODEReal y, ODEReal z);
	};
}

#endif