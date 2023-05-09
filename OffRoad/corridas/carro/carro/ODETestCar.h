#ifndef ODETESTCAR_H
#define ODETESTCAR_H

#include "ODETest.h"

namespace ODE
{
	/// Para testar o carro.
	class ODETestCar : public ODETest
	{
	public:
		ODETestCar();
		~ODETestCar();

		virtual bool createContact(ODEContact& contact, ODEGeometry* geom1
			, ODEGeometry* geom2);
		virtual void command(int c);
		virtual void loop();
		virtual void draw();
		virtual void start();

	protected:
		static const int LEFT = -1;
		static const int RIGHT = 1;

		ODECar car;
		ODECarControl carControl;
		ODEReal direction;
		ODEReal throttle;
		ODEReal brake;
		bool handbrake;
		bool lockCamera;

		ODEReal throttleAmount;
		ODEReal brakeAmount;
	};
}

#endif