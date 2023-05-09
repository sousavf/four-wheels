#include "ODEHeaders.h"

using namespace ODE;

ODECarDefinition ODECarDefinition::get(Type t)
{
	switch (t)
	{
	case Default:
	default:
		return ODECarDefinition(
					ODEVector3(2.0f, 3.2f, 0.1f)	// chassisSize
					, 15.0f		// chassisMass
					, 0.4f		// wheelRadius
					, 1.0f		// wheelMass
					, 0.4f		// wheelWidth
					, ODEVector3(0.45f, 0.25f, 0.95f)	// wheelOffset
					, 0.2f		// wheelFudgeFactor
					, 180		// suspensionSpring
					, 50		// suspensionDamping
					, 100		// brakeForce
					, 10000		// throttleForce
					, 100		// handbrake force
					, 100		// steerForce
					, 4.0f		// steerSpeed
					, 1			// steerLimit
					, 1			// steerFactor
					, 15000	// swayForce
					, 500		// swayLimit
					, 0.5f		// differentialFactor
					, 0.00001f	// perpendicularFDSFactor
					, ODEContactDefinition(
						-1		// mu
						, -1	// mu2
						, 0.9f	// bouncyness
						, -1	// velocityThreshold
						, -1	// erp
						, -1	// cfm
						, -1	// velocity
						, -1	// velocity2
						, 0.004f// fds
						, -1)	// fds2
				);
		//return ODECarDefinition(
		//			ODEVector3(1.87f, 3.88f, 0.61f)		// chassisSize
		//			, 3.8f		// chassisMass
		//			, 0.65f		// wheelRadius
		//			, 0.09f		// wheelMass
		//			, 0.6f		// wheelWidth
		//			, ODEVector3(0.65f, 0.55f, 0.25f)	// wheelOffset
		//			, 0.2f		// wheelFudgeFactor
		//			, 90		// suspensionSpring
		//			, 5.6f		// suspensionDamping
		//			, 40		// brakeForce
		//			, 100		// throttleForce
		//			, 10000		// handbrake force
		//			, 8			// steerForce
		//			, 4			// steerSpeed
		//			, 1			// steerLimit
		//			, 1			// steerFactor
		//			, 15000		// swayForce
		//			, 150		// swayLimit
		//			, 0.5f		// differentialFactor
		//			, 0.004f	// perpendicularFDSFactor
		//			, ODEContactDefinition(
		//				2.5f	// mu
		//				, -1	// mu2
		//				, 0.9f	// bouncyness
		//				, -1	// velocityThreshold
		//				, -1	// erp
		//				, -1	// velocity
		//				, -1	// velocity2
		//				, 0.04f	// fds
		//				, -1)	// fds2
		//		);
	}
}




/// Cria uma nova definição de um carro.
ODECarDefinition::ODECarDefinition(
				ODEVector3 chassisSize,
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
				const ODEContactDefinition &cDef)
				:contactDefinition(cDef)
{
	this->chassisSize = chassisSize;
	this->chassisMass = chassisMass;
	this->wheelRadius = wheelRadius;
	this->wheelMass = wheelMass;
	this->wheelWidth = wheelWidth;
	this->wheelOffset = wheelOffset;
	this->wheelFudgeFactor = wheelFudgeFactor;
	this->suspensionSpring = suspensionSpring;
	this->suspensionDamping = suspensionDamping;
	this->brakeForce = brakeForce;
	this->throttleForce = throttleForce;
	this->handbrakeForce = handbrakeForce;
	this->steerForce = steerForce;
	this->steerSpeed = steerSpeed;
	this->steerLimit = steerLimit;
	this->steerFactor = steerFactor;
	this->swayForce = swayForce;
	this->swayLimit = swayLimit;
	this->differentialFactor = differentialFactor;
	this->perpendicularFDSFactor = perpendicularFDSFactor;
}



/// Destrói a definição.
ODECarDefinition::~ODECarDefinition()
{
}



/// Define o tamanho do chassis.
void ODECarDefinition::setChassisSize(const ODEVector3 &s)
{
	this->chassisSize = s;
}



/// Define a massa do chassis.
void ODECarDefinition::setChassisMass(ODEReal mass)
{
	this->chassisMass = mass;
}



/// Define o raio das rodas.
void ODECarDefinition::setWheelRadius(ODEReal radius)
{
	this->wheelRadius = radius;
}



/// Define a massa das rodas.
void ODECarDefinition::setWheelMass(ODEReal mass)
{
	this->wheelMass = mass;
}



/// Define a largura das rodas.
void ODECarDefinition::setWheelWidth(ODEReal width)
{
	this->wheelWidth = width;
}



/// Define a posição relativa das rodas.
void ODECarDefinition::setWheelOffset(const ODEVector3 &offset)
{
	this->wheelOffset = offset;
}



/// Define o valor do parâmetro fudge factor das juntas das rodas.
void ODECarDefinition::setWheelFudgeFactor(ODEReal fudgeFactor)
{
	this->wheelFudgeFactor = fudgeFactor;
}



/// Define a spring da suspensão.
void ODECarDefinition::setSuspensionSpring(ODEReal spring)
{
	this->suspensionSpring = spring;
}



/// Define o damping suspensão.
void ODECarDefinition::setSuspensionDamping(ODEReal damping)
{
	this->suspensionDamping = damping;
}



/// Define a força aplicada ao travão.
void ODECarDefinition::setBrakeForce(ODEReal force)
{
	this->brakeForce = force;
}



/// Define a força aplicada ao acelerador.
void ODECarDefinition::setThrottleForce(ODEReal force)
{
	this->throttleForce = force;
}



/// Define a força aplicada ao travão de mão.
void ODECarDefinition::setHandbrakeForce(ODEReal force)
{
	this->handbrakeForce = force;
}



/// Define a força aplicada ao virar as rodas.
void ODECarDefinition::setSteerForce(ODEReal force)
{
	this->steerForce = force;
}



/// Define a velocidade de viragem das rodas.
void ODECarDefinition::setSteerSpeed(ODEReal speed)
{
	this->steerSpeed = speed;
}



/// Define o limite de viragem das rodas.
void ODECarDefinition::setSteerLimit(ODEReal limit)
{
	this->steerLimit = limit;
}



/// Define o factor de rodagem das rodas.
void ODECarDefinition::setSteerFactor(ODEReal factor)
{
	this->steerFactor = factor;
}



/// Define a força multiplicativa do anti-sway.
void ODECarDefinition::setSwayForce(ODEReal force)
{
	this->swayForce = force;
}



/// Define o limite da força anti-sway aplicada.
void ODECarDefinition::setSwayLimit(ODEReal limit)
{
	this->swayLimit = limit;
}



/// Define o factor aplicado ao diferencial.
void ODECarDefinition::setDifferentialFactor(ODEReal factor)
{
	this->differentialFactor = factor;
}



/// Define os parâmetros de contacto.
void ODECarDefinition::setContactDefinition(const ODEContactDefinition &cDef)
{
	this->contactDefinition = cDef;
}



/// Devolve o tamanho do chassis.
const ODEVector3 ODECarDefinition::getChassisSize() const
{
	return ODEVector3(this->chassisSize);
}



/// Devolve a massa do chassis.
ODEReal ODECarDefinition::getChassisMass() const
{
	return this->chassisMass;
}



/// Devolve o raio das rodas.
ODEReal ODECarDefinition::getWheelRadius() const
{
	return this->wheelRadius;
}



/// Devolve a massa das rodas.
ODEReal ODECarDefinition::getWheelMass() const
{
	return this->wheelMass;
}



/// Devolve a largura das rodas.
ODEReal ODECarDefinition::getWheelWidth() const
{
	return this->wheelWidth;
}



/// Devolve um vector com a posição das rodas em relação ao chassis.
const ODEVector3 ODECarDefinition::getWheelOffset() const
{
	return ODEVector3(this->wheelOffset);
}



/// Devolve o valor do parâmetro fudge factor aplicado às juntas das rodas.
ODEReal ODECarDefinition::getWheelFudgeFactor() const
{
	return this->wheelFudgeFactor;
}



/// Devolve a spring da suspensão.
ODEReal ODECarDefinition::getSuspensionSpring() const
{
	return this->suspensionSpring;
}



/// Devolve o damping da suspensão.
ODEReal ODECarDefinition::getSuspensionDamping() const
{
	return this->suspensionDamping;
}



/// Devolve a força aplicada no travão.
ODEReal ODECarDefinition::getBrakeForce() const
{
	return this->brakeForce;
}



/// Devolve a força aplicada no acelerador.
ODEReal ODECarDefinition::getThrottleForce() const
{
	return this->throttleForce;
}



/// Devolve a força aplicada no travão de mão.
ODEReal ODECarDefinition::getHandbrakeForce() const
{
	return this->handbrakeForce;
}



/// Devolve a força de rotação das rodas.
ODEReal ODECarDefinition::getSteerForce() const
{
	return this->steerForce;
}



/// Devolve a velocidade de rotação das rodas.
ODEReal ODECarDefinition::getSteerSpeed() const
{
	return this->steerSpeed;
}



/// Devolve o limite de rotação das rodas.
ODEReal ODECarDefinition::getSteerLimit() const
{
	return this->steerLimit;
}



/// Devolve o factor de rotação das rodas.
ODEReal ODECarDefinition::getSteerFactor() const
{
	return this->steerFactor;
}



/// Define a força de anti-sway aplicada.
ODEReal ODECarDefinition::getSwayForce() const
{
	return this->swayForce;
}



/// Define o limite de força anti-sway aplicado.
ODEReal ODECarDefinition::getSwayLimit() const
{
	return this->swayLimit;
}



/// Devolve o factor aplicado ao diferencial.
ODEReal ODECarDefinition::getDifferentialFactor() const
{
	return this->differentialFactor;
}



/// Devolve os parâmetros de contactos que vão ser usados pelas rodas.
const ODEContactDefinition& ODECarDefinition::getContactDefinition() const
{
	return this->contactDefinition;
}



/// Devolve o valor do factor da força perpendicular que é aplicada às rodas.
ODEReal ODECarDefinition::getPerpendicularFDSFactor() const
{
	return this->perpendicularFDSFactor;
}