#ifndef ODEFIXEDJOINT_H
#define ODEFIXEDJOINT_H

#include "ODERequirements.h"

namespace ODE
{
	/// Representa uma junta do tipo fixed. Serve para juntar 2 corpos
	/// mantendo sempre a mesma posição e rotação relativa.
	class ODEFixedJoint : public ODEJoint
	{
	public:
		ODEFixedJoint(ODEWorld &world);
		ODEFixedJoint(ODEWorld &world, const ODEJointGroup &group);
		~ODEFixedJoint();

		virtual void setParameter(Parameter p, ODEReal value, int axis = 1);
		virtual ODEReal getParameter(Parameter p, int axis = 1) const;

		void setFixed();
		virtual Type getType() const;
	};
}

#endif