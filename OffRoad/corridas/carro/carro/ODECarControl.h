#ifndef ODECARCONTROL_H
#define ODECARCONTROL_H

#include "ODERequirements.h"

namespace ODE
{
	/// Usado para controlar os inputs para um carro.
	class ODECarControl
	{
	public:
		ODECarControl(ODECar &car, ODEReal steerAmount = 1
			, ODEReal throttleAmount = 1, ODEReal brakeAmount = 1);
		~ODECarControl();

		void steerLeft();
		void steerRight();
		void throttle();
		void brake();
		void handbrake();
		void reverse();
		void update();

		void setSteer(ODEReal steer);
		void setSteerAmount(ODEReal amount);
		void setThrottle(ODEReal throttle);
		void setThrottleAmount(ODEReal amount);
		void setBrake(ODEReal brake);
		void setBrakeAmount(ODEReal amount);
		void setHandbrake(bool handbrake);
		void setHandbrakeRate(ODEReal rate);

		ODEReal getSteer() const;
		ODEReal getSteerAmount()const;
		ODEReal getThrottle() const;
		ODEReal getThrottleAmount() const;
		ODEReal getBrake() const;
		ODEReal getBrakeAmount() const;
		ODEReal getHandbrakeRate() const;
		bool handbraking() const;
		bool isForward() const;

	protected:
		static const int LEFT = -1;
		static const int RIGHT = 1;

		ODECar *car;
		ODEReal steer;
		ODEReal steerAmount;
		ODEReal throttlePosition;
		ODEReal throttleAmount;
		ODEReal brakePosition;
		ODEReal brakeAmount;
		bool isHandbraking;
		ODEReal handbrakeRate;
		ODEReal handbrakeTimer;

		static void updateControl(ODEReal &control, ODEReal amount);
	};
}

#endif