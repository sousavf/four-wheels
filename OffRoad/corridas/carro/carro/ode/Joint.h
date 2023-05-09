#ifndef Joint_h
#define Joint_h

#include <ode/ode.h>
#include "Object.h"

class Joint
{
	public:
		enum MotorParameter
		{
			LowStop,
			HighStop,
			Velocity,
			Velocity2,
			MaximumForce,
			MaximumForce2,
			FudgeFactor,
			Bouncyness,
			CFM,
			StopERP,
			StopCFM,
			SuspensionERP,
			SuspensionCFM
		};

		Joint();
		~Joint();

		dJointID ID() const;
        void Attach(Object &obj1, Object &obj2);
		void Attach(dBodyID body1, dBodyID body2);
		void Detach();

	protected:
		dJointID joint;

		static int GetODEParameter(MotorParameter param);
};

#endif