#ifndef ODEVECTOR3_H
#define ODEVECTOR3_H

#include "ODERequirements.h"

namespace ODE
{
	/// Representa um vector com 3 posições que normalmente representam
	/// as coordenadas x, y, z, seja de uma posição, ou velocidade, ...
	class ODEVector3
	{
	public:
		ODEVector3();
		ODEVector3(ODEReal x, ODEReal y, ODEReal z);
		ODEVector3(const ODEVector3 &v);
		~ODEVector3();

		ODEReal dotProduct(const ODEVector3& v) const;
		ODEVector3 crossProduct(const ODEVector3 &v) const;
		ODEReal length() const;

		ODEVector3& operator = (const dReal* v);
		ODEVector3& operator = (const ODEVector3& v);
		ODEVector3 operator * (const ODEVector3& v) const;
		ODEVector3 operator - (const ODEVector3& v) const;
		ODEVector3 operator + (const ODEVector3& v) const;
		ODEVector3 operator / (const ODEVector3& v) const;
		ODEVector3 operator + () const;
		ODEVector3 operator - () const;
		ODEVector3 operator * (ODEReal r) const;
		ODEVector3 operator / (ODEReal r) const;
		friend ODEVector3 operator * (ODEReal r, const ODEVector3& v);
		friend ODEVector3 operator / (ODEReal r, const ODEVector3& v);
		friend ODEVector3 operator + (ODEReal r, const ODEVector3& v);
		friend ODEVector3 operator - (ODEReal r, const ODEVector3& v);
		friend ODEVector3 operator + (const ODEVector3& v, ODEReal r);
		friend ODEVector3 operator - (const ODEVector3& v, ODEReal r);
		ODEReal& operator [] (int index);
		ODEReal operator [] (int index) const;
		bool operator == (const ODEVector3& v) const;

	protected:
		ODEReal data[3];

		void Init(ODEReal x, ODEReal y, ODEReal z);
	};
}

#endif