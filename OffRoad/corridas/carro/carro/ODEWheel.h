#ifndef ODEWHEEL_H
#define ODEWHEEL_H

#include "ODERequirements.h"

namespace ODE
{
	/// Representa uma roda (geometria de cilindro e massa de esfera).
	class ODEWheel : public ODESimpleObject
	{
	public:
		enum Position
		{
			FrontLeft,
			FrontRight,
			BackLeft,
			BackRight
		};

		ODEWheel(ODECar& car, const ODEVector3 position, ODEReal mass
			, ODEReal radius, ODEReal width, ODEReal perpendicularFDSFactor
			, ODEReal fudgeFactor = 0.2f
			, const ODEContactDefinition &cDef = ODEContactDefinition());
		~ODEWheel();

		void setRadius(ODEReal radius);
		void setWidth(ODEReal width);
		void setMass(ODEReal mass);
		void setSuspension(ODEReal spring, ODEReal damping);
		void setSteerLimit(ODEReal limit);
		void setSteerFactor(ODEReal factor);
		void setSteerForce(ODEReal force);
		void setSteerSpeed(ODEReal speed);
		void setSteer(ODEReal position);
		void setPowerFactor(ODEReal factor);
		void setBrakeFactor(ODEReal factor);
		void setPerpendicularFDSFactor(ODEReal factor);

		ODEReal getRadius() const;
		ODEReal getWidth() const;
		ODEHinge2Joint& getJoint();
		ODEReal getSuspensionSpring() const;
		ODEReal getSuspensionDamping() const;
		ODEReal getSteerLimit() const;
		ODEReal getSteerFactor() const;
		ODEReal getSteerForce() const;
		ODEReal getSteerSpeed() const;
		ODEReal getSteer() const;
		ODEReal getPowerFactor() const;
		ODEReal getBrakeFactor() const;
		ODEReal getPerpendicularFDSFactor() const;

		ODEReal getRPM() const;
		void update(ODEReal desiredRPM, ODEReal powerForce, ODEReal brakeForce);
		void applyPerpendicularFDS(ODEContact& contact);

	protected:
		ODEHinge2Joint joint;
		ODEReal steerLimit;
		ODEReal steerFactor;
		ODEReal steerForce;
		ODEReal steerSpeed;
		ODEReal spring;
		ODEReal damping;
		ODEReal powerFactor;
		ODEReal brakeFactor;
		ODEReal perpendicularFDSFactor;

		void adjustSteerLimits();
	};
}

#endif