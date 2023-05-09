#include "ODEHeaders.h"

using namespace ODE;

/// Cria um controlo para o carro car.
ODECarControl::ODECarControl(ODECar &car, ODEReal steerAmount, ODEReal throttleAmount, ODEReal brakeAmount)
{
	this->car = &car;
	this->steer = 0;
	this->steerAmount = steerAmount;
	this->throttlePosition = 0;
	this->throttleAmount = throttleAmount;
	this->brakePosition = 0;
	this->brakeAmount = brakeAmount;
	this->handbrakeTimer = 0;
	this->handbrakeRate = 14;
	this->isHandbraking = false;
}



/// Destr�i o controlo do carro.
ODECarControl::~ODECarControl()
{
}



/// Vira para a esquerda.
void ODECarControl::steerLeft()
{
	if (this->steer > LEFT)
	{
		this->steer -= this->steerAmount;
	}
}



/// Vira para a direita.
void ODECarControl::steerRight()
{
	if (this->steer < RIGHT)
	{
		this->steer += this->steerAmount;
	}
}



/// Incrementa a posi��o do acelerador.
void ODECarControl::throttle()
{
	if (this->throttlePosition < 1)
	{
		this->throttlePosition += this->throttleAmount;
	}
}



/// Incrementa a posi��o do trav�o.
void ODECarControl::brake()
{
	if (this->brakePosition < 1)
	{
		this->brakePosition += this->brakeAmount;
	}
}



/// Activa o trav�o de m�o durante handbrakeRate passos.
void ODECarControl::handbrake()
{
	if (!this->isHandbraking)
	{
		this->isHandbraking = true;
		this->handbrakeTimer = 0;
	}
}



/// Se estiver a andar para a frente passa a andar para tr�s,
/// sen�o passa a andar para a frente.
void ODECarControl::reverse()
{
	this->car->setThrottleForce(-this->car->getThrottleForce());
}



/// Actualiza o controlo e o carro.
void ODECarControl::update()
{
	this->car->setEnable(true);
	this->car->setThrottlePosition(this->throttlePosition);
	this->car->setBrakePosition(this->brakePosition);
	this->car->setSteer(this->steer);
	this->car->update();

	if (this->isHandbraking)
	{
		this->car->handbrake();
		this->handbrakeTimer++;

		if (this->handbrakeTimer >= this->handbrakeRate)
		{
			this->isHandbraking = false;
		}
	}
	updateControl(this->steer, this->steerAmount);
	updateControl(this->brakePosition, this->brakeAmount);
	updateControl(this->throttlePosition, this->throttleAmount);
}



/// Reduz o valor de controlo em 25% de amount, mas nunca deixa passar o valor 0.
void ODECarControl::updateControl(ODEReal &control, ODEReal amount)
{
	bool positive = (control > 0);

	if (fabs(control) > 0)
	{
		control += (control > 0 ? -1: 1) * 1.0f * amount;

		if ( (positive && control < 0) || (!positive && control > 0) )
		{
			control = 0;
		}
	}
}




/// Define a posi��o da direc��o.
void ODECarControl::setSteer(ODEReal steer)
{
	this->steer = steer;
}



/// Define a quantidade por que � incrementada a direc��o.
void ODECarControl::setSteerAmount(ODEReal amount)
{
	this->steerAmount = amount;
}



/// Define a posi��o do acelerador.
void ODECarControl::setThrottle(ODEReal throttle)
{
	this->throttlePosition = throttle;
}



/// Define a quantidade por que � incrementada a posi��o do acelerador.
void ODECarControl::setThrottleAmount(ODEReal amount)
{
	this->throttleAmount = amount;
}



/// Define o valor da posi��o do trav�o.
void ODECarControl::setBrake(ODEReal brake)
{
	this->brakePosition = brake;
}



/// Define a quantidade por que � incrementada a posi��o do trav�o.
void ODECarControl::setBrakeAmount(ODEReal amount)
{
	this->brakeAmount = amount;
}



/// Define se se est� a fazer hanbrake.
void ODECarControl::setHandbrake(bool handbrake)
{
	this->isHandbraking = handbrake;

	if (this->isHandbraking)
	{
		this->handbrakeTimer = 0;
	}
}



/// Define por quantos passos � que o handbrake � aplicado.
void ODECarControl::setHandbrakeRate(ODEReal rate)
{
	this->handbrakeRate = rate;
}



/// Indica o valor da posi��o da direc��o.
ODEReal ODECarControl::getSteer() const
{
	return this->steer;
}



/// Indica a quantidade por que � incrementada a direc��o.
ODEReal ODECarControl::getSteerAmount()const
{
	return this->steerAmount;
}



/// Indica o valor da posi��o do acelerador.
ODEReal ODECarControl::getThrottle() const
{
	return this->throttlePosition;
}



/// Indica a quantidade por que � incrementada a posi��o do acelerador.
ODEReal ODECarControl::getThrottleAmount() const
{
	return this->throttleAmount;
}



/// Indica o valor da posi��o do trav�o.
ODEReal ODECarControl::getBrake() const
{
	return this->brakePosition;
}



/// Indica a quantidade por que � incrementada a posi��o do trav�o.
ODEReal ODECarControl::getBrakeAmount() const
{
	return this->brakeAmount;
}



/// Indica se est� a efecutar um hanbrake.
bool ODECarControl::handbraking() const
{
	return this->isHandbraking;
}



/// Indica por quantos passos da simula��o � que o handbrake � aplicado.
ODEReal ODECarControl::getHandbrakeRate() const
{
	return this->handbrakeRate;
}



/// Indica se o carro est� a andar para frente.
bool ODECarControl::isForward() const
{
	return this->car->getThrottleForce() > 0;
}