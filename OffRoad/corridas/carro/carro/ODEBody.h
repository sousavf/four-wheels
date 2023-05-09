#ifndef ODEBODY_H
#define ODEBODY_H

#include "ODERequirements.h"

namespace ODE
{
	/// Representa um corpo. Um corpo tem massa, velocidade, gravidade, ...
	class ODEBody
	{
	public:
		ODEBody(ODEWorld &world);
		~ODEBody();

		void setPosition(const ODEVector3 &pos);
		void setRotation(const ODEMatrix3 &rot);
		void setQuaternion(const ODEQuaternion &orientation);
		void setLinearVelocity(const ODEVector3 &vel);
		void setAngularVelocity(const ODEVector3 &vel);
		void setMass(const ODEMass &mass);
        void setForce(const ODEVector3 &force);
        void setTorque(const ODEVector3 &torque);

		const ODEVector3 getPosition() const;
		const ODEMatrix3 getRotation() const;
		const ODEQuaternion getQuaternion() const;
		const ODEVector3 getLinearVelocity() const;
		const ODEVector3 getAngularVelocity() const;
		const ODEMass& getMass();
		const ODEVector3 getForce() const;
        const ODEVector3 getTorque() const;

		void addForce(const ODEVector3 &force);
		void addTorque(const ODEVector3 &torque);
		void addRelativeForce(const ODEVector3 &force);
		void addRelativeTorque(const ODEVector3 &torque);
		void addForceAtPosition(const ODEVector3 &force, const ODEVector3 &pos);
		void addForceAtRelativePosition(const ODEVector3 &force, const ODEVector3 &pos);
		void addRelativeForceAtPosition(const ODEVector3 &force, const ODEVector3 &pos);
		void addRelativeForceAtRelativePosition(const ODEVector3 &force, const ODEVector3 &pos);

		void setEnable(bool enable);
		bool isEnabled() const;
		dBodyID getID() const;

	protected:
		dBodyID id;
		ODEMass mass;
		ODEWorld *world;
	};
}

#endif
