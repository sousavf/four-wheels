#ifndef ODEVECTOR2_H
#define ODEVECTOR2_H

#include "ODERequirements.h"

namespace ODE
{
	/// Representa um vector com 2 posições que normalmente representam
	/// coordenadas em x, y.
	class ODEVector2
	{
	public:
		ODEVector2();
		ODEVector2(ODEReal x, ODEReal y);
		ODEVector2(const ODEVector2 &v);
		~ODEVector2();

		ODEVector2& operator = (const ODEVector2 &v);
		ODEReal& operator [] (int index);
		ODEReal operator [] (int index) const;

	protected:
		ODEReal data[2];

		void Init(ODEReal x, ODEReal y);
	};
}

#endif