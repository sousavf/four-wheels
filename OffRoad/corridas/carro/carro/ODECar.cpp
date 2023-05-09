#include "ODEHeaders.h"
#include "Utilities.h"

using namespace ODE;

/// Constrói um carro com a definição default.
ODECar::ODECar(ODEWorld &world):ODEComplexObject(world)
{
	Init(world, ODECarDefinition::get(ODECarDefinition::Default));
}



/// Constrói um carro com a definição def.
ODECar::ODECar(ODEWorld &world, const ODECarDefinition &def):ODEComplexObject(world)
{
	Init(world, def);
}



/// Define os parâmetros do carro através da definição def.
void ODECar::Init(ODEWorld &world, const ODECarDefinition &def)
{
	ODEVector3 pos;
	ODEWheel **wheels;

	pos[2] = def.getWheelRadius() - def.getWheelOffset()[2] * def.getChassisSize()[2];
	this->chassis = new ODEBox(world, this->space, def.getChassisMass(), def.getChassisSize());
	this->chassis->setPosition(pos);
	this->wheelOffset = def.getWheelOffset();
	wheels = new ODEWheel*[4];

	for (int i = 0; i < 4; i++)
	{
		wheels[i] = new ODEWheel(*this, wheelPosition(i), def.getWheelMass()
			, def.getWheelRadius(), def.getWheelWidth(), def.getPerpendicularFDSFactor()
			, def.getWheelFudgeFactor()
			, def.getContactDefinition());
		wheels[i]->setSuspension(def.getSuspensionSpring(), def.getSuspensionDamping());
		this->objects.push_back(wheels[i]);
		this->joints.push_back(&(wheels[i]->getJoint()));
	}
	this->objects.push_back(chassis);

	// rodas da frente
	for (int i = 0; i < 2; i++)
	{
		getWheel(i).setSteerFactor(def.getSteerFactor());
		getWheel(i).setSteerForce(def.getSteerForce());
		getWheel(i).setSteerSpeed(def.getSteerSpeed());
		getWheel(i).setSteerLimit(def.getSteerLimit());
		getWheel(i).setPowerFactor(1);
		getWheel(i).setBrakeFactor(0.5f);
	}

	// rodas de trás
	for (int i = 2; i < 4; i++)
	{
		getWheel(i).setPowerFactor(1);
		getWheel(i).setBrakeFactor(0.5f);
	}
	this->swayTime = 0;
	this->antiSway = true;
	this->swayRate = this->world->getStepTime();
	this->swayForce = def.getSwayForce();
	this->swayLimit = def.getSwayLimit();
	this->throttleForce = def.getThrottleForce();
	this->brakeForce = def.getBrakeForce();
	this->handbrakeForce = def.getHandbrakeForce();
	this->throttlePosition = 0;
	this->brakePosition = 0;
	this->steerPosition = 0;
	this->useDifferential = true;
	this->differentialFactor = def.getDifferentialFactor();
}



/// Destrói o carro.
ODECar::~ODECar()
{
	this->joints.empty(); // para não chamar destrutores das juntas no ~ODEComplexObject
						  // porque não é preciso, porque nos destrutores das rodas já destrói juntas
}



/// Devolve a posição da roda correspondente a i.
/// Não tem em conta que o carro pode estar inclinado, assume sempre
/// que o carro está "pousado" ao chão, mas pode estar virado.
ODEVector3 ODECar::wheelPosition(int i)
{
	ODEVector3 chassisPosition, chassisSize, wheelPosition;
	ODEReal angle, carAngle, wheelAngle, h, x, y;

	if (i < 0 || i > 3)
	{
		return ODEVector3();
	}
	chassisPosition = this->chassis->getPosition();
	chassisSize = this->chassis->getSize();
	carAngle = this->chassis->getQuaternion().getEulerAngles()[2];
	y = this->wheelOffset[0] * chassisSize[0];
	x = this->wheelOffset[1] * chassisSize[1];
	h = sqrt( powf(x, 2) + powf(y, 2) );
	wheelAngle = Utilities::ToDegrees(acosf(x / h));

	if (i == 0)
	{
		wheelAngle = wheelAngle + 180;
	}
	else if (i == 1)
	{
		wheelAngle = wheelAngle + 2 * (90 - wheelAngle);
	}
	else if (i == 2)
	{
		wheelAngle = -wheelAngle;
	}
	angle = carAngle - (90 - wheelAngle);
	angle = Utilities::ToRadians(angle);
	wheelPosition[0] = chassisPosition[0] + cosf(angle) * h;
	wheelPosition[1] = chassisPosition[1] + sinf(angle) * h;
	wheelPosition[2] = chassisPosition[2] + this->wheelOffset[2] * chassisSize[2];

	return wheelPosition;
}



/// Define a suspensão.
void ODECar::setSuspension(ODEReal spring, ODEReal damping)
{
	for (int i = 0; i < 4; i++)
	{
		getWheel(i).setSuspension(spring, damping);
	}
}



/// Define a direcção (-1 a 1).
void ODECar::setSteer(ODEReal position)
{
	this->steerPosition = position;
}



/// Aplica anti-sway? Método para o carro não virar.
void ODECar::setApplyAntiSwayBars(bool apply)
{
	this->antiSway = apply;
}



/// Define a força que é aplicada no anti-sway.
void ODECar::setSwayForce(ODEReal force)
{
	this->swayForce = force;
}



/// Define o limite do anti-sway.
void ODECar::setSwayLimit(ODEReal limit)
{
	this->swayLimit = limit;
}



/// Define o rate do anti-sway.
void ODECar::setSwayRate(ODEReal sway)
{
	this->swayRate = sway;
}



/// Define a força do travão.
void ODECar::setBrakeForce(ODEReal force)
{
	this->brakeForce = force;
}



/// Define a posição do travão.
void ODECar::setBrakePosition(ODEReal position)
{
	this->brakePosition = position;
}



/// Define a posição do acelerador.
void ODECar::setThrottlePosition(ODEReal  position)
{
	this->throttlePosition = position;
}



/// 
void ODECar::setThrottleForce(ODEReal limit)
{
	this->throttleForce = limit;
}



/// Define a força aplicada no travão de mão.
void ODECar::setHandbrakeForce(ODEReal force)
{
	this->handbrakeForce = force;
}



/// Define se usa um diferencial.
void ODECar::setUseDifferential(bool use)
{
	this->useDifferential = use;
}



/// Define o factor que é usado pelo diferencial para definir a diferença
/// entre a velocidade e rodagem das rodas esquerdas e direitas.
void ODECar::setDifferentialFactor(ODEReal factor)
{
	this->differentialFactor = factor;
}



/// Indica se aplica anti-sway ou não.
bool ODECar::getApplyAntiSwayBars() const
{
	return this->antiSway;
}



/// Devolve a força de anti-sway.
ODEReal ODECar::getSwayForce() const
{
	return this->swayForce;
}



/// Devolve o limite de anti-sway.
ODEReal ODECar::getSwayLimit() const
{
	return this->swayLimit;
}



/// Devolve o ritmo de anti-sway.
ODEReal ODECar::getSwayRate() const
{
	return this->swayRate;
}



/// Devolve a roda correspondente a position.
ODEWheel& ODECar::getWheelAt(ODEWheel::Position position)
{
	return *((ODEWheel*)this->objects[(int)position]);
}



/// Devolve a roda correspondente a i.
ODEWheel& ODECar::getWheel(int i)
{
	return *((ODEWheel*)this->objects[i]);
}



/// Devolve a junta correspondente a position.
const ODEHinge2Joint& ODECar::getJoint(ODEWheel::Position position) const
{
	return *((ODEHinge2Joint*)this->joints[(int)position]);
}




/// Devolve a junta correspondente a i.
ODEHinge2Joint& ODECar::getJoint(int i)
{
	return *((ODEHinge2Joint*)this->joints[i]);
}



/// Devolve o chassis.
ODEBox& ODECar::getChassis()
{
	return *(this->chassis);
}



/// Devolve a força aplica ao travão.
ODEReal ODECar::getBrakeForce() const
{
	return this->brakeForce;
}



/// Devolve a posição do travão.
ODEReal ODECar::getBrakePosition() const
{
	return this->brakePosition;
}



/// Devolve a posição do acelerador.
ODEReal ODECar::getThrottlePosition() const
{
	return this->throttlePosition;
}



/// Força do acelerador
ODEReal ODECar::getThrottleForce() const
{
	return this->throttleForce;
}



/// Devolve a força aplicada no travão de mão.
ODEReal ODECar::getHandbrakeForce() const
{
	return this->handbrakeForce;
}



/// 
ODEReal ODECar::getPowerAtRPM(ODEReal rpm) const
{
	ODEReal position, dx, ti;
	unsigned int i;

	position = rpm * (1 / this->throttleForce);
	i = (unsigned int)position;
	dx = position - (ODEReal)i;
	ti = (i == 0 ? 2.5f : 8.0f);

	return ti + dx * (8.0f - ti);
}



/// Indica se usa um diferencial.
bool ODECar::getUseDifferential() const
{
	return this->useDifferential;
}


/// Devolve o factor usado pelo diferencial para definir a diferença
/// entre as velocidades e rodagens das rodas esquerdas/direitas.
ODEReal ODECar::getDifferentialFactor() const
{
	return this->differentialFactor;
}



/// Devolve o valor máximo de RPM das rodas.
ODEReal ODECar::getMaxWheelRPM()
{
	ODEReal rpm;

	for (int i = 0; i < 4; i++)
	{
		if ( (i == 0) || (getWheel(i).getRPM() > rpm) )
		{
			rpm = getWheel(i).getRPM();
		}
	}

	return rpm;
}



/// Actualiza o carro.
void ODECar::update()
{
	ODEReal rpm, desiredRPM, powerForce, brakeForce;

	rpm = getMaxWheelRPM();
	desiredRPM = this->throttleForce * this->throttlePosition;
	powerForce = this->getPowerAtRPM(rpm);
	brakeForce = this->brakeForce * this->brakePosition;

	if (this->useDifferential)
	{
		differential(desiredRPM, powerForce, brakeForce);
	}
	else
	{
		getWheel(0).setSteer(this->steerPosition);
		getWheel(1).setSteer(this->steerPosition);

		for (int i = 0; i < 4; i++)
		{
			getWheel(i).update(desiredRPM, powerForce, brakeForce);
		}
	}
	
	if (this->antiSway)
	{
		this->swayTime += this->world->getStepTime();

		if (this->swayTime >= this->swayRate)
		{
			antiSwayBars();
			this->swayTime = 0;
		}
	}
}



/// Aplica o differential ao carro.
void ODECar::differential(ODEReal desiredRPM, ODEReal powerForce, ODEReal brakeForce)
{
	ODEReal leftRPM, rightRPM, leftSteer, rightSteer;

	leftRPM = rightRPM = 1;
	leftSteer = rightSteer = 1;

	// virar à direita
	if (this->steerPosition > 0.1f)
	{
		rightRPM = 1 - 0.5f * this->differentialFactor;
		leftRPM = 1 + 0.5f * this->differentialFactor;
		//leftSteer = 1 - this->differentialFactor;
		leftSteer = 1 - 0.5f * this->differentialFactor;
		rightSteer = 1 + 0.5f * this->differentialFactor;
	}
	// virar à esquerda
	else if (this->steerPosition < -0.1f)
	{
		leftRPM = 1 - 0.5f * this->differentialFactor;
		rightRPM = 1 + 0.5f * this->differentialFactor;
		//rightSteer = 1 - this->differentialFactor;
		rightSteer = 1 - 0.5f * this->differentialFactor;
		leftSteer = 1 + 0.5f * this->differentialFactor;
	}
	getWheelAt(ODEWheel::FrontLeft).setSteer(leftSteer * this->steerPosition);
	getWheelAt(ODEWheel::FrontRight).setSteer(rightSteer * this->steerPosition);
	getWheelAt(ODEWheel::FrontLeft).update(leftRPM * desiredRPM, powerForce, brakeForce);
	getWheelAt(ODEWheel::FrontRight).update(rightRPM * desiredRPM, powerForce, brakeForce);
	getWheelAt(ODEWheel::BackLeft).update(leftRPM * desiredRPM, powerForce, brakeForce);
	getWheelAt(ODEWheel::BackRight).update(rightRPM * desiredRPM, powerForce, brakeForce);
}



/// Aplica um travão de mão.
void ODECar::handbrake()
{
	ODEVector3 rotation, rotPerpendicular;
	ODEReal velocity;

	for (int i = 0; i < 4; i++)
	{
		getJoint(i).setParameter(ODEJoint::Velocity, 0, 2);
		getJoint(i).setParameter(ODEJoint::MaximumForce, this->handbrakeForce, 2);
	}
	velocity = getLinearVelocity().length();
	rotation = getQuaternion().getEulerAngles();

	for (int i = 0; i < 2; i++)
	{
		rotPerpendicular[i] = rotation[i] - 135;
		rotPerpendicular[i] = Utilities::ToRadians(rotPerpendicular[i]);
	}
	addForceAtPosition(
		ODEVector3(cos(rotPerpendicular[0]) * velocity * velocity * 10
			, sin(rotPerpendicular[1]) * velocity * velocity * 10, 0)
		, ODEVector3(cos(rotation[0]) * getChassis().getSize()[0] + getPosition()[0]
			, sin(rotation[1]) * getChassis().getSize()[1] + getPosition()[1]
			, getPosition()[2]));
}



/// Aplica um método para o carro não se despistar (virar).
void ODECar::antiSwayBars()
{
	ODEVector3 axis, anchor1, anchor2;
	ODEReal displacement, amount;

	for( int i = 0; i < 4; i++)
	{
		axis = getJoint(i).getAxis1();
		anchor1 = getJoint(i).getAnchor();
		anchor2 = getJoint(i).getAnchor2();
		displacement = (anchor1 - anchor2).dotProduct(axis);

		if (displacement > 0)
		{
			amount = displacement * this->swayForce;

			if (amount > this->swayLimit)
			{
				amount = this->swayLimit;
			}
			getWheel(i).addForce(-axis * amount);
			getWheel(i ^ 1).addForce(axis * amount);
		}
	}
}



/// Define a posição do carro.
void ODECar::setPosition(const ODEVector3 &pos)
{
	ODEVector3 position;

	this->chassis->getBody().setPosition(pos);

	for (int i = 0; i < 4; i++)
	{
		position = wheelPosition(i);
		getWheel(i).setPosition(position);
		getJoint(i).setAnchor(position);
	}
}



/// Coloca o chassis e as rodas com a rotação rot.
void ODECar::setRotation(const ODEMatrix3 &rot)
{
	this->chassis->getBody().setRotation(rot);
	
	for (int i = 0; i < 4; i++)
	{
		getWheel(i).setRotation(rot);
	}
	setPosition(this->chassis->getPosition());
}



/// Coloca o chassis e as rodas com o quaternion orientation.
void ODECar::setQuaternion(const ODEQuaternion &orientation)
{
	this->chassis->getBody().setQuaternion(orientation);
	
	for (int i = 0; i < 4; i++)
	{
		getWheel(i).setQuaternion(orientation);
	}
	setPosition(this->chassis->getPosition());
}



/// Põe o chassis E as rodas à velocidade vel.
void ODECar::setLinearVelocity(const ODEVector3 &vel)
{
	this->chassis->getBody().setLinearVelocity(vel);

	for (int i = 0; i < 4; i++)
	{
		getWheel(i).setLinearVelocity(vel);
	}
}



/// Põe o chassis E as rodas à velocidade  angular vel.
void ODECar::setAngularVelocity(const ODEVector3 &vel)
{
	this->chassis->getBody().setAngularVelocity(vel);

	for (int i = 0; i < 4; i++)
	{
		getWheel(i).setAngularVelocity(vel);
	}
}



/// Põe o chassis com força force.
void ODECar::setForce(const ODEVector3 &force)
{
	this->chassis->getBody().setForce(force);
}



/// Põe o chassis com torque torque.
void ODECar::setTorque(const ODEVector3 &torque)
{
	this->chassis->getBody().setTorque(torque);
}



/// 
void ODECar::setCategoryBits(unsigned long bits)
{
	for (int i = 0; i < (int)this->objects.size(); i++)
	{
		this->objects[i]->setCategoryBits(bits);
	}
}



/// 
void ODECar::setCollideBits(unsigned long bits)
{
	for (int i = 0; i < (int)this->objects.size(); i++)
	{
		this->objects[i]->setCollideBits(bits);
	}
}



/// 
const ODEVector3 ODECar::getPosition() const
{
	return chassis->getPosition();
}



/// 
const ODEMatrix3 ODECar::getRotation() const
{
	return chassis->getBody().getRotation();
}



/// 
const ODEQuaternion ODECar::getQuaternion() const
{
	return this->chassis->getBody().getQuaternion();
}



/// 
const ODEVector3 ODECar::getLinearVelocity() const
{
	return this->chassis->getLinearVelocity();
}



/// 
const ODEVector3 ODECar::getAngularVelocity() const
{
	return this->chassis->getAngularVelocity();
}



/// 
const ODEVector3 ODECar::getForce() const
{
	return this->chassis->getForce();
}



/// 
const ODEVector3 ODECar::getTorque() const
{
	return this->chassis->getTorque();
}



/// 
unsigned long ODECar::getCategoryBits() const
{
	return this->chassis->getCategoryBits();
}



/// 
unsigned long ODECar::getCollideBits() const
{
	return this->chassis->getCollideBits();
}



/// 
void ODECar::addForce(const ODEVector3 &force)
{
	this->chassis->addForce(force);
}



/// 
void ODECar::addTorque(const ODEVector3 &torque)
{
	this->chassis->addTorque(torque);
}



/// 
void ODECar::addRelativeForce(const ODEVector3 &force)
{
	this->chassis->addRelativeForce(force);
}



/// 
void ODECar::addRelativeTorque(const ODEVector3 &torque)
{
	this->chassis->addRelativeTorque(torque);
}



/// 
void ODECar::addForceAtPosition(const ODEVector3 &force, const ODEVector3 &pos)
{
	this->chassis->addForceAtPosition(force, pos);
}



/// 
void ODECar::addForceAtRelativePosition(const ODEVector3 &force, const ODEVector3 &pos)
{
	this->chassis->addForceAtRelativePosition(force, pos);
}



/// 
void ODECar::addRelativeForceAtPosition(const ODEVector3 &force, const ODEVector3 &pos)
{
	this->chassis->addRelativeForceAtPosition(force, pos);
}



/// 
void ODECar::addRelativeForceAtRelativePosition(const ODEVector3 &force, const ODEVector3 &pos)
{
	this->chassis->addRelativeForceAtRelativePosition(force, pos);
}



/// 
void ODECar::setEnable(bool enable)
{
	for (int i = 0; i < (int)this->objects.size(); i++)
	{
		this->objects[i]->setEnable(enable);
	}
}



/// 
bool ODECar::isEnabled() const
{
	return this->chassis->isEnabled();
}
