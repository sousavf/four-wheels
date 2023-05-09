#ifndef ODEVECTOR4_H
#define ODEVECTOR4_H

#include "ODERequirements.h"

namespace ODE
{
	/// Representa um vector com 4 posições que normalmente representam
	/// um plano a*x + b*y + c*z = d.
	class ODEVector4
	{
	public:
		ODEVector4();
		ODEVector4(ODEReal a, ODEReal b, ODEReal c, ODEReal d);
		ODEVector4(const ODEVector4 &v);
		~ODEVector4();

		ODEVector4& operator = (const dReal* v);
		ODEReal& operator [] (int index);

	protected:
		ODEReal data[4];

		void Init(ODEReal a, ODEReal b, ODEReal c, ODEReal d);
	};
}

#endif