#ifndef ODESLIDERJOINT_H
#define ODESLIDERJOINT_H

#include "ODERequirements.h"

namespace ODE
{
	/// Representa uma junta do tipo slider.
	class ODESliderJoint : public ODEJoint
	{
	public:
		ODESliderJoint(ODEWorld &world);
		ODESliderJoint(ODEWorld &world, const ODEJointGroup &group);
		~ODESliderJoint();

		virtual void setParameter(Parameter p, ODEReal value, int axis = 1);
		virtual void setAxis(const ODEVector3 &axis);

		virtual ODEReal getParameter(Parameter p, int axis = 1) const;
		virtual const ODEVector3& getAxis();

		virtual void addForce(ODEReal force);
		virtual Type getType() const;
		virtual ODEReal getPosition() const;
		virtual ODEReal getPositionRate() const;

	protected:
		ODEVector3 axis;
	};
}

#endif