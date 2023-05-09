#ifndef ODEJOINT_H
#define ODEJOINT_H

#include "ODERequirements.h"

namespace ODE
{
	/// Representa uma junta. Uma junta serve para construir objectos complexos.
	/// É uma articulação que indica como é que os objectos se encontram posicionados
	/// relativamente um ao outro e como funciona a rotação.
	/// Usar as subclasses para um tipo específico de junta.
	class ODEJoint
	{
	public:
		enum Parameter
		{
			LowStop = dParamLoStop,
			HighStop = dParamHiStop,
			Velocity = dParamVel,
			MaximumForce = dParamFMax,
			FudgeFactor = dParamFudgeFactor,
			Bouncyness = dParamBounce,
			CFM = dParamCFM,
			StopERP = dParamStopERP,
			StopCFM = dParamStopCFM,
			SuspensionERP = dParamSuspensionERP,
			SuspensionCFM = dParamSuspensionCFM
		};

		enum Type
		{
			Ball = dJointTypeBall,
			Hinge = dJointTypeHinge,
			Slider = dJointTypeSlider,
			Contact =  dJointTypeContact,
			Universal = dJointTypeUniversal,
			Hinge2 = dJointTypeHinge2,
			Fixed = dJointTypeFixed,
			AMotor = dJointTypeAMotor
		};
		
		static bool areConnected(const ODEBody &body1, const ODEBody &body2);
		static bool areConnectedExcluding(const ODEBody &body1, const ODEBody &body2, Type t);

		ODEJoint(ODEWorld &world);
		~ODEJoint();

		virtual void setParameter(Parameter p, ODEReal value, int axis = 1) = 0;
		virtual ODEReal getParameter(Parameter p, int axis = 1) const = 0;

		void attach(const ODEBody &body1, const ODEBody &body2);
		void detach();
		ODEBody& getBody1();
		ODEBody& getBody2();
		dJointID getID() const;
		virtual Type getType() const = 0;

	protected:
		static int Param(Parameter p, int axis);

		dJointID id;
		ODEWorld *world;

		ODEBody& getBody(int index);
	};
}

#endif