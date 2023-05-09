#ifndef ODEMATRIX3_H
#define ODEMATRIX3_H

#include "ODERequirements.h"

namespace ODE
{
	/// Representa uma matriz (3x4) para rotações num vector de 12 posições.
	class ODEMatrix3
	{
	public:
		ODEMatrix3();
		ODEMatrix3(const ODEReal* m);
		ODEMatrix3(const ODEMatrix3 &m);
		~ODEMatrix3();

		void fromAxisAndAngle(ODEReal ax, ODEReal ay, ODEReal az, ODEReal angle);

		ODEMatrix3& operator = (const dReal* m);
		ODEReal& operator [] (int index);
		ODEReal operator [] (int index) const;

	protected:
		ODEReal data[12];

		void Init(const ODEReal* m);
	};
}

#endif