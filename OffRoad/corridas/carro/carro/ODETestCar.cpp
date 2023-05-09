#include "ODETestCar.h"
#include <drawstuff/drawstuff.h>

using namespace ODE;

#pragma warning(disable: 4355)


/// Cria o teste.
ODETestCar::ODETestCar()
	:car(this->world),carControl(this->car)
{
	this->lockCamera = true;
}



/// Destrói o teste.
ODETestCar::~ODETestCar()
{
}



/// r	reset
/// ,	esquerda
/// .	direita
/// a	acelerar
/// z	travar
///		travão de mão
/// x	reverse
/// c	prende/desprende a câmara ao carro
void ODETestCar::command(int c)
{
	switch(c)
	{
		case 'r':
			this->world.reset();
			break;

		case ',':
			carControl.steerLeft();
			break;

		case '.':
			carControl.steerRight();
			break;

		case 'a':
			carControl.throttle();
			break;

		case 'z':
			carControl.brake();
			break;

		case 'x':
			carControl.reverse();
			break;

		case ' ':
			carControl.handbrake();
			break;

		case 'c':
			this->lockCamera = !this->lockCamera;
			break;
	}
}



/// Não faz nada.
void ODETestCar::loop()
{
	carControl.update();
	//printf("%.2f\n", this->car.getLinearVelocity().length() * 3.6);
}



/// Desenha.
void ODETestCar::draw()
{
	dVector3 s;

	dsSetColorAlpha(1, 0, 0, 1.0f);
	dGeomBoxGetLengths(this->car.getChassis().getGeomID(), s);
	dsDrawBox(dGeomGetPosition(this->car.getChassis().getGeomID())
		, dGeomGetRotation(this->car.getChassis().getGeomID()), s);

	dsSetColorAlpha(0, 0, 1, 1.0f);
	dsDrawCylinder(dGeomGetPosition(this->car.getWheelAt(ODE::ODEWheel::FrontLeft).getGeomID())
		, dGeomGetRotation(this->car.getWheelAt(ODE::ODEWheel::FrontLeft).getGeomID())
		, this->car.getWheelAt(ODE::ODEWheel::FrontLeft).getWidth(), this->car.getWheelAt(ODE::ODEWheel::FrontLeft).getRadius());
	dsDrawCylinder(dGeomGetPosition(this->car.getWheelAt(ODE::ODEWheel::FrontRight).getGeomID())
		, dGeomGetRotation(this->car.getWheelAt(ODE::ODEWheel::FrontRight).getGeomID())
		, this->car.getWheelAt(ODE::ODEWheel::FrontRight).getWidth(), this->car.getWheelAt(ODE::ODEWheel::FrontRight).getRadius());
	dsDrawCylinder(dGeomGetPosition(this->car.getWheelAt(ODE::ODEWheel::BackLeft).getGeomID())
		, dGeomGetRotation(this->car.getWheelAt(ODE::ODEWheel::BackLeft).getGeomID())
		, this->car.getWheelAt(ODE::ODEWheel::BackLeft).getWidth(), this->car.getWheelAt(ODE::ODEWheel::BackLeft).getRadius());
	dsDrawCylinder(dGeomGetPosition(this->car.getWheelAt(ODE::ODEWheel::BackRight).getGeomID())
		, dGeomGetRotation(this->car.getWheelAt(ODE::ODEWheel::BackRight).getGeomID())
		, this->car.getWheelAt(ODE::ODEWheel::BackRight).getWidth(), this->car.getWheelAt(ODE::ODEWheel::BackRight).getRadius());

	if (this->lockCamera)
	{
		float pos[3], rot[3];

		pos[0] = this->car.getPosition()[0];
		pos[1] = this->car.getPosition()[1] - 7;
		pos[2] = 15;
		rot[0] = 90;//this->car.getQuaternion().getEulerAngle(0);
		rot[1] = -60;
		rot[2] = 0;// + this->car.getQuaternion().getEulerAngle(2);
		dsSetViewpoint (pos, rot);
	}
}



/// Inicia o teste.
void ODETestCar::start()
{
	this->world.setStepTime(2.5f);
	this->world.addObject(&this->car);
}



/// Trata das colisões.
bool ODETestCar::createContact(ODEContact& contact, ODEGeometry* geom1, ODEGeometry* geom2)
{
	contact.setFrictionMode(ODEContact::BothFrictionPyramids);
	contact.setCoulombFriction(2.5f);
	contact.setBouncyness(0.9f);
	contact.setForceDependentSlip(0.04f);

	return true;
}