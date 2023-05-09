#ifndef ODECARDEFINITION_H
#define ODECARDEFINITION_H

#include "ODERequirements.h"

namespace ODE
{
	/// Representa a definição de um carro.
	class ODECarDefinition
	{
	public:
		enum Type
		{
			Default
		};

		static ODECarDefinition get(Type t);

		ODECarDefinition(ODEVector3 chassisSize,
						ODEReal chassisMass,
						ODEReal wheelRadius,
						ODEReal wheelMass,
						ODEReal wheelWidth,
						ODEVector3 wheelOffset,
						ODEReal wheelFudgeFactor,
						ODEReal suspensionSpring,
						ODEReal suspensionDamping,
						ODEReal brakeForce,
						ODEReal throttleForce,
						ODEReal handbrakeForce,
						ODEReal steerForce,
						ODEReal steerSpeed,
						ODEReal steerLimit,
						ODEReal steerFactor,
						ODEReal swayForce,
						ODEReal swayLimit,
						ODEReal differentialFactor,
						ODEReal perpendicularFDSFactor,
						const ODEContactDefinition &cDef);
		~ODECarDefinition();

		void setChassisSize(const ODEVector3 &s);
		void setChassisMass(ODEReal mass);
		void setWheelRadius(ODEReal radius);
		void setWheelMass(ODEReal mass);
		void setWheelWidth(ODEReal width);
		void setWheelOffset(const ODEVector3 &offset);
		void setWheelFudgeFactor(ODEReal fudgeFactor);
		void setSuspensionSpring(ODEReal spring);
		void setSuspensionDamping(ODEReal damping);
		void setBrakeForce(ODEReal force);
		void setThrottleForce(ODEReal force);
		void setHandbrakeForce(ODEReal force);
		void setSteerForce(ODEReal force);
		void setSteerSpeed(ODEReal speed);
		void setSteerLimit(ODEReal limit);
		void setSteerFactor(ODEReal factor);
		void setSwayForce(ODEReal force);
		void setSwayLimit(ODEReal limit);
		void setDifferentialFactor(ODEReal factor);
		void setContactDefinition(const ODEContactDefinition &cDef);
		void setPerpendicularFDSFactor(ODEReal factor);

		const ODEVector3 getChassisSize() const;
		ODEReal getChassisMass() const;
		ODEReal getWheelRadius() const;
		ODEReal getWheelMass() const;
		ODEReal getWheelWidth() const;
		const ODEVector3 getWheelOffset() const;
		ODEReal getWheelFudgeFactor() const;
		ODEReal getSuspensionSpring() const;
		ODEReal getSuspensionDamping() const;
		ODEReal getBrakeForce() const;
		ODEReal getThrottleForce() const;
		ODEReal getHandbrakeForce() const;
		ODEReal getSteerForce() const;
		ODEReal getSteerSpeed() const;
		ODEReal getSteerLimit() const;
		ODEReal getSteerFactor() const;
		ODEReal getSwayForce() const;
		ODEReal getSwayLimit() const;
		ODEReal getDifferentialFactor() const;
		const ODEContactDefinition& getContactDefinition() const;
		ODEReal getPerpendicularFDSFactor() const;

	protected:
		ODEVector3 chassisSize;
		ODEReal chassisMass;
		ODEReal wheelRadius;
		ODEReal wheelMass;
		ODEReal wheelWidth;
		ODEVector3 wheelOffset;
		ODEReal wheelFudgeFactor;
		ODEReal suspensionSpring;
		ODEReal suspensionDamping;
		ODEReal brakeForce;
		ODEReal throttleForce;
		ODEReal handbrakeForce;
		ODEReal steerForce;
		ODEReal steerSpeed;
		ODEReal steerLimit;
		ODEReal steerFactor;
		ODEReal swayForce;
		ODEReal swayLimit;
		ODEReal differentialFactor;
		ODEContactDefinition contactDefinition;
		ODEReal perpendicularFDSFactor;
	};
}

#endif