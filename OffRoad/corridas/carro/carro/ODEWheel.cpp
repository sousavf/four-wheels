#include "ODEHeaders.h"

using namespace ODE;

static const bool CYLINDER_MASS = true;

/// Cria uma roda.
ODEWheel::ODEWheel(ODECar& car, const ODEVector3 position, ODEReal mass
			, ODEReal radius, ODEReal width, ODEReal perpendicularFDSFactor
			, ODEReal fudgeFactor
			, const ODEContactDefinition &cDef)
			:ODESimpleObject(car.getWorld()),joint(car.getWorld())
{
	ODEQuaternion rot;

	if (CYLINDER_MASS)
	{
		this->body.setMass(ODECylinderMass(mass, ODE::Z, radius, width));
	}
	else
	{
		this->body.setMass(ODESphereMass(mass, radius));
	}
	this->geometry = new ODECylinderGeometry(car.getWorld(), car.getSpace(), radius, width, cDef);
	this->geometry->setBody(this->body);
	rot.fromAxisAndAngle(0, 1, 0, 0.5 * M_PI);
	this->geometry->setQuaternion(rot);
	this->setPosition(position);
	this->joint.attach(car.getChassis().getBody(), this->body);
	this->joint.setAnchor(position);
	this->joint.setAxis1(ODEVector3(0, 0, 1));
	this->joint.setAxis2(ODEVector3(1, 0, 0));
	this->joint.setParameter(ODEJoint::FudgeFactor, fudgeFactor);
	setSteerFactor(0);
	setSteerLimit(0);
	setSteerForce(0);
	setSteerSpeed(0);
	setPowerFactor(0);
	setBrakeFactor(0);
	setSteer(0.0);
	setPerpendicularFDSFactor(perpendicularFDSFactor);
}



/// Destrói a roda.
ODEWheel::~ODEWheel()
{
}



/// Define a massa da roda.
void ODEWheel::setMass(ODEReal mass)
{
	ODEReal radius;

	radius = ((ODECylinderGeometry*)this->geometry)->getRadius();

	if (CYLINDER_MASS)
	{
		ODEReal width;

		width = ((ODECylinderGeometry*)this->geometry)->getLength();
		this->body.setMass(ODECylinderMass(mass, ODE::Z, radius, width));
	}
	else
	{
		this->body.setMass(ODESphereMass(mass, radius));
	}
}



/// Define o raio da roda.
void ODEWheel::setRadius(ODEReal radius)
{
	ODEReal mass;

	mass = this->body.getMass().getValue();
	
	if (CYLINDER_MASS)
	{
		ODEReal width;

		width = ((ODECylinderGeometry*)this->geometry)->getLength();
		this->body.setMass(ODECylinderMass(mass, ODE::Z, radius, width));
	}
	else
	{
		this->body.setMass(ODESphereMass(mass, radius));
	}
	((ODECylinderGeometry*)this->geometry)->setRadius(radius);

}



/// Define o comprimento da roda.
void ODEWheel::setWidth(ODEReal width)
{
	((ODECylinderGeometry*)this->geometry)->setLength(width);

	if (CYLINDER_MASS)
	{
		ODEReal mass, radius;

		mass = this->body.getMass().getValue();
		radius = ((ODECylinderGeometry*)this->geometry)->getRadius();
		this->body.setMass(ODECylinderMass(mass, ODE::Z, radius, width));
	}
}






/// Define os parâmetros da suspensão.
void ODEWheel::setSuspension(ODEReal spring, ODEReal damping)
{
	ODEReal step = 0.001f * this->world->getStepTime();

	this->spring = spring;
	this->damping = damping;
	this->joint.setParameter(ODEJoint::SuspensionERP, step * spring / (step * spring + damping));
	this->joint.setParameter(ODEJoint::SuspensionCFM, 1.0f / (step * spring + damping));
}



/// Define o limite de viragem.
void ODEWheel::setSteerLimit(ODEReal limit)
{
	this->steerLimit = limit;
	adjustSteerLimits();
}



/// Define com que factor é que vira
void ODEWheel::setSteerFactor(ODEReal factor)
{
	this->steerFactor = factor;
	adjustSteerLimits();
}



/// Ajusta o limite de viragem.
void ODEWheel::adjustSteerLimits()
{
	this->joint.setParameter(ODEJoint::HighStop, this->steerLimit * fabs(this->steerFactor));
	this->joint.setParameter(ODEJoint::LowStop, -this->steerLimit * fabs(this->steerFactor));
}



/// Define que força usa para virar.
void ODEWheel::setSteerForce(ODEReal force)
{
	this->steerForce = force;
}



/// Define a velocidade com que vira.
void ODEWheel::setSteerSpeed(ODEReal speed)
{
	this->steerSpeed = speed;
}



/// Define a posição de viragem.
void ODEWheel::setSteer(ODEReal position)
{
	if ( (this->steerFactor != 0) && (this->steerLimit != 0) )
	{
		ODEReal velocity, steerAngle;
		
		steerAngle = position * this->steerLimit;
		velocity = (steerAngle * this->steerFactor - this->joint.getAngle1())
					* (this->steerSpeed * fabs(this->steerFactor));
		this->joint.setParameter(ODEJoint::Velocity, velocity);
		this->joint.setParameter(ODEJoint::MaximumForce, this->steerForce);
	}
}



/// Define o factor de aceleração
void ODEWheel::setPowerFactor(ODEReal factor)
{
	this->powerFactor = factor;
}



/// Define o factor de travagem.
void ODEWheel::setBrakeFactor(ODEReal factor)
{
	this->brakeFactor = factor;
}



/// Define o factor da força perpendicular que é aplicada às rodas.
void ODEWheel::setPerpendicularFDSFactor(ODEReal factor)
{
	this->perpendicularFDSFactor = factor;
}



/// Devolve o raio da roda.
ODEReal ODEWheel::getRadius() const
{
	return ((ODECylinderGeometry*)this->geometry)->getRadius();
}



/// Devolve o comprimento da roda.
ODEReal ODEWheel::getWidth() const
{
	return ((ODECylinderGeometry*)this->geometry)->getLength();
}



/// Devolve a junta (suspensão) da roda.
ODEHinge2Joint& ODEWheel::getJoint()
{
	return this->joint;
}



/// Devolve o valor de spring da suspensão.
ODEReal ODEWheel::getSuspensionSpring() const
{
	return this->spring;
}



/// Devolve o valor de damping da suspensão.
ODEReal ODEWheel::getSuspensionDamping() const
{
	return this->damping;
}



/// Devolve o limite de viragem.
ODEReal ODEWheel::getSteerLimit() const
{
	return this->steerLimit;
}



/// Devolve o factor com que vira.
ODEReal ODEWheel::getSteerFactor() const
{
	return this->steerFactor;
}


 
/// Define a força com que vira.
ODEReal ODEWheel::getSteerForce() const
{
	return this->steerForce;
}



/// Define a velocidade com que vira.
ODEReal ODEWheel::getSteerSpeed() const
{
	return this->steerSpeed;
}



/// Indica a posição de viragem.
ODEReal ODEWheel::getSteer() const
{
	return (this->steerFactor != 0 ? this->joint.getAngle1() : 0);
}



/// Devolve o factor de aceleração.
ODEReal ODEWheel::getPowerFactor() const
{
	return this->powerFactor;
}



/// Devolve o factor de travagem.
ODEReal ODEWheel::getBrakeFactor() const
{
	return this->brakeFactor;
}



/// Devolve as rotações por minuto da roda.
ODEReal ODEWheel::getRPM() const
{
	return (this->powerFactor > 0 ? this->joint.getParameter(ODEJoint::Velocity, 2) : 0);
}



/// Devolve o valor do factor da força perpendicular que é aplicada às rodas.
ODEReal ODEWheel::getPerpendicularFDSFactor() const
{
	return this->perpendicularFDSFactor;
}



/// Actualiza a roda.
void ODEWheel::update(ODEReal desiredRPM, ODEReal powerForce, ODEReal brakeForce)
{
	ODEReal force = powerForce * this->powerFactor - brakeForce * this->brakeFactor;

	if (force > 0)
	{
		this->joint.setParameter(ODEJoint::Velocity, desiredRPM, 2);
		this->joint.setParameter(ODEJoint::MaximumForce, force, 2);
	}
	else
	{
		this->joint.setParameter(ODEJoint::Velocity, 0.01f, 2);
		this->joint.setParameter(ODEJoint::MaximumForce, -force, 2);
	}
}



/// Aplica uma força perpendicular à direcção da roda.
void ODEWheel::applyPerpendicularFDS(ODEContact& contact)
{
	ODEQuaternion rot, q;
	ODEVector3 up, forward, velocity;

	velocity = getLinearVelocity();

	if (velocity.length() > 0)
	{
		q = getQuaternion();
		up = q * ODEVector3(0, 1, 0);
		rot.fromAxisAndAngle(up[0], up[1], up[2], getSteer());
		forward = rot * (getQuaternion() * ODEVector3(0, 0, 1));
		contact.setFrictionDirection1(forward);
		contact.setForceDependentSlip2(velocity.length() * this->perpendicularFDSFactor);
	}
}