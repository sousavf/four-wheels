#ifndef ODECAR_H
#define ODECAR_H

#include "ODERequirements.h"
#include <vector>

using namespace std;

namespace ODE
{
	/// Representa um carro de 4 rodas.
	class ODECar : public ODEComplexObject
	{
	public:
		ODECar(ODEWorld &world);
		ODECar(ODEWorld &world, const ODECarDefinition &def);
		~ODECar();

		virtual void setPosition(const ODEVector3 &pos);
		virtual void setRotation(const ODEMatrix3 &rot);
		virtual void setQuaternion(const ODEQuaternion &orientation);
		virtual void setLinearVelocity(const ODEVector3 &vel);
		virtual void setAngularVelocity(const ODEVector3 &vel);
        virtual void setForce(const ODEVector3 &force);
        virtual void setTorque(const ODEVector3 &torque);
		virtual void setCategoryBits(unsigned long bits);
		virtual void setCollideBits(unsigned long bits);

		virtual const ODEVector3 getPosition() const;
		virtual const ODEMatrix3 getRotation() const;
		virtual const ODEQuaternion getQuaternion() const;
		virtual const ODEVector3 getLinearVelocity() const;
		virtual const ODEVector3 getAngularVelocity() const;
		virtual const ODEVector3 getForce() const;
        virtual const ODEVector3 getTorque() const;
		virtual unsigned long getCategoryBits() const;
		virtual unsigned long getCollideBits() const;

		virtual void addForce(const ODEVector3 &force);
		virtual void addTorque(const ODEVector3 &torque);
		virtual void addRelativeForce(const ODEVector3 &force);
		virtual void addRelativeTorque(const ODEVector3 &torque);
		virtual void addForceAtPosition(const ODEVector3 &force, const ODEVector3 &pos);
		virtual void addForceAtRelativePosition(const ODEVector3 &force, const ODEVector3 &pos);
		virtual void addRelativeForceAtPosition(const ODEVector3 &force, const ODEVector3 &pos);
		virtual void addRelativeForceAtRelativePosition(const ODEVector3 &force, const ODEVector3 &pos);

		virtual void setEnable(bool enable);
		virtual bool isEnabled() const;

		void setSuspension(ODEReal spring, ODEReal damping);
		void setSteer(ODEReal position);
		void setApplyAntiSwayBars(bool apply);
		void setSwayForce(ODEReal force);
		void setSwayLimit(ODEReal limit);
		void setSwayRate(ODEReal sway);
		void setBrakeForce(ODEReal force);
		void setBrakePosition(ODEReal position);
		void setThrottlePosition(ODEReal  position);
		void setThrottleForce(ODEReal limit);
		void setHandbrakeForce(ODEReal force);
		void setUseDifferential(bool use);
		void setDifferentialFactor(ODEReal factor);

		bool getApplyAntiSwayBars() const;
		ODEReal getSwayForce() const;
		ODEReal getSwayLimit() const;
		ODEReal getSwayRate() const;
		ODEReal getBrakeForce() const;
		ODEReal getBrakePosition() const;
		ODEReal getThrottlePosition() const;
		ODEReal getThrottleForce() const;
		ODEReal getHandbrakeForce() const;
		bool getUseDifferential() const;
		ODEReal getDifferentialFactor() const;
		ODEWheel& getWheel(int i);

		ODEReal getMaxWheelRPM();
		ODEReal getPowerAtRPM(ODEReal rpm) const;
		ODEWheel& getWheelAt(ODEWheel::Position position);
		const ODEHinge2Joint& getJoint(ODEWheel::Position position) const;
		ODEBox& getChassis();
		void update();
		void handbrake();
		
	protected:
		ODEReal swayForce;
		ODEReal swayLimit;
		ODEReal swayRate;
		ODEReal swayTime;
		bool antiSway;
		ODEReal brakeForce;
		ODEReal brakePosition;
		ODEReal throttlePosition;
		ODEReal throttleForce;
		ODEBox *chassis;
		ODEReal handbrakeForce;
		bool useDifferential;
		ODEReal steerPosition;
		ODEReal differentialFactor;
		ODEVector3 wheelOffset;
		ODEReal perpendicularFDSFactor;

		void Init(ODEWorld &world, const ODECarDefinition &def);
		ODEHinge2Joint& getJoint(int i);
		void antiSwayBars();
		void differential(ODEReal desiredRPM, ODEReal powerForce, ODEReal brakeForce);
		ODEVector3 wheelPosition(int i);
	};
}

#endif