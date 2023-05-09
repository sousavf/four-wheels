#ifndef ODEHINGE2JOINT_H
#define ODEHINGE2JOINT_H

#include "ODERequirements.h"

namespace ODE
{
	/// Representa uma junta do tipo hinge2 que é ideal para modelar
	/// a junta de um carro que liga o chassis a uma roda.
	class ODEHinge2Joint : public ODEJoint
	{
	public:
		ODEHinge2Joint(ODEWorld &world);
		ODEHinge2Joint(ODEWorld &world, const ODEJointGroup &group);
		~ODEHinge2Joint();

		virtual void setParameter(Parameter p, ODEReal value, int axis = 1);
		virtual void setAnchor(const ODEVector3 &axis);
		virtual void setAxis1(const ODEVector3 &axis);
		virtual void setAxis2(const ODEVector3 &axis);

		virtual ODEReal getParameter(Parameter p, int axis = 1) const;
		virtual const ODEVector3 getAnchor() const;
		virtual const ODEVector3 getAnchor2() const;
		virtual const ODEVector3 getAxis1() const;
		virtual const ODEVector3 getAxis2() const;

		virtual void addTorques(ODEReal torque1, ODEReal torque2);
		virtual ODEReal getAngle1() const;
		virtual ODEReal getAngle1Rate() const;
		virtual ODEReal getAngle2Rate() const;
		virtual Type getType() const;
	};
}

#endif