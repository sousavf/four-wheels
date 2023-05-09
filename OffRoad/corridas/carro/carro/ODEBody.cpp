#include "ODEHeaders.h"

using namespace ODE;

/// Cria um novo corpo pertencente a world.
ODEBody::ODEBody(ODEWorld &world):mass()
{
	this->world = &world;
	this->id = dBodyCreate(world.getID());
	dBodySetData(this->id, (void*)this);
}



/// Destrói o corpo.
ODEBody::~ODEBody()
{
	dBodyDestroy(this->id);
}



/// Define uma posição para o corpo. Deve ser usado para estabelecer
/// as condições iniciais de uma simulação ou para um eventual reset.
/// Para posicionar um corpo devem ser usadas forças.
void ODEBody::setPosition(const ODEVector3 &pos)
{
	dBodySetPosition(this->id, (ODEReal)pos[0], (ODEReal)pos[1], (ODEReal)pos[2]);
	this->setEnable(true);
}



/// Define a rotação do corpo. Deve ser usado para estabelecer
/// as condições iniciais de uma simulação ou para um eventual reset.
/// Para rodar um corpo devem ser usadas forças.
void ODEBody::setRotation(const ODEMatrix3 &rot)
{
	dMatrix3 r;

	for (int i = 0; i < 12; i++)
	{
		r[i] = (dReal)rot[i];
	}
	dBodySetRotation(this->id, r);
	this->setEnable(true);
}



/// Define uma orientação para o corpo. Deve ser usado para estabelecer
/// as condições iniciais de uma simulação ou para um eventual reset.
/// Para rodar um corpo devem ser usadas forças.
void ODEBody::setQuaternion(const ODEQuaternion &orientation)
{
	dQuaternion q;

	q[0] = (dReal)orientation[0];
	q[1] = (dReal)orientation[1];
	q[2] = (dReal)orientation[2];
	q[3] = (dReal)orientation[3];
	dBodySetQuaternion(this->id, q);
	this->setEnable(true);
}



/// Define a velocidade linear do corpo. Só deve ser usado em casos em que queremos
/// fazer um reset, por exemplo. Não se deve forçar uma velocidade específica num corpo,
/// apenas aplicar forças.
void ODEBody::setLinearVelocity(const ODEVector3 &vel)
{
	dBodySetLinearVel(this->id, (dReal)vel[0], (dReal)vel[1], (dReal)vel[2]);
	this->setEnable(true);
}



/// Define a velocidade angular do corpo. Só deve ser usado em casos em que queremos
/// fazer um reset, por exemplo. Não se deve forçar uma velocidade específica num corpo,
/// apenas aplicar forças.
void ODEBody::setAngularVelocity(const ODEVector3 &vel)
{
	dBodySetAngularVel(this->id, (dReal)vel[0], (dReal)vel[1], (dReal)vel[2]);
	this->setEnable(true);
}



/// Define a massa associada ao corpo.
void ODEBody::setMass(const ODEMass &mass)
{
	dBodySetMass(this->id, &(mass.getMass()));
}



/// Define as forças acumuladas no corpo. É útil para situações em que queremos
/// retirar as forças aplicadas a um corpo (para reset). Para aplicarmos uma força
/// a um corpo devemos usar os métodos addForce...
void ODEBody::setForce(const ODEVector3 &force)
{
	dBodySetForce(this->id, (dReal)force[0], (dReal)force[1], (dReal)force[2]);
	this->setEnable(true);
}



/// Define as forças angulares acumuladas no corpo. É útil para situações em que queremos
/// retirar as forças aplicadas a um corpo (para reset). Para aplicarmos uma força angular
/// a um corpo devemos usar os métodos addTorque...
void ODEBody::setTorque(const ODEVector3 &torque)
{
	dBodySetTorque(this->id, (dReal)torque[0], (dReal)torque[1], (dReal)torque[2]);
	this->setEnable(true);
}



/// Devolve a posição do corpo.
const ODEVector3 ODEBody::getPosition() const
{
	ODEVector3 position;

	const dReal* pos = dBodyGetPosition(this->id);
	position = pos;

	return position;
}



/// Devolve a rotação do corpo.
const ODEMatrix3 ODEBody::getRotation() const
{
	ODEMatrix3 rotation;

	const dReal* rot = dBodyGetRotation(this->id);
	rotation = rot;

	return rotation;
}



/// Devolve a orientação do corpo.
const ODEQuaternion ODEBody::getQuaternion() const
{
	ODEQuaternion quaternion;

	const dReal* o = dBodyGetQuaternion(this->id);
	quaternion = o;

	return quaternion;
}



/// Devolve a velocidade linear do corpo.
const ODEVector3 ODEBody::getLinearVelocity() const
{
	ODEVector3 velocity;

	const dReal* vel = dBodyGetLinearVel(this->id);
	velocity = vel;

	return velocity;
}



/// Devolve a velocidade angular do corpo.
const ODEVector3 ODEBody::getAngularVelocity() const
{
	ODEVector3 angularVelocity;

	const dReal* vel = dBodyGetAngularVel(this->id);
	angularVelocity = vel;

	return angularVelocity;
}



/// Devolve a massa associada ao corpo.
const ODEMass& ODEBody::getMass()
{
	dMass m;

	dBodyGetMass(this->id, &m);
	this->mass = m;

	return this->mass;
}



/// Devolve um vector com as forças acumuladas no corpo.
const ODEVector3 ODEBody::getForce() const
{
	ODEVector3 force;

	const dReal* f = dBodyGetForce(this->id);
	force = f;

	return force;
}



/// Devolve um vector com as forças angulares acumuladas no corpo.
const ODEVector3 ODEBody::getTorque() const
{
	ODEVector3 torque;

	const dReal* t = dBodyGetTorque(this->id);
	torque = t;

	return torque;
}



/// Aplica uma força ao corpo.
void ODEBody::addForce(const ODEVector3 &force)
{
	this->setEnable(true);
	dBodyAddForce(this->id, (dReal)force[0], (dReal)force[1], (dReal)force[2]);
}



/// Aplica uma força angular.
void ODEBody::addTorque(const ODEVector3 &torque)
{
	this->setEnable(true);
	dBodyAddTorque(this->id, (dReal)torque[0], (dReal)torque[1], (dReal)torque[2]);
}



/// Aplica força relativa ao frame de referência do corpo.
void ODEBody::addRelativeForce(const ODEVector3 &force)
{
	this->setEnable(true);
	dBodyAddRelForce(this->id, (dReal)force[0], (dReal)force[1], (dReal)force[2]);
}



/// Aplica uma força angular relativa ao frame de referência do corpo.
void ODEBody::addRelativeTorque(const ODEVector3 &torque)
{
	this->setEnable(true);
	dBodyAddRelTorque(this->id, (dReal)torque[0], (dReal)torque[1], (dReal)torque[2]);
}



/// Aplica uma força numa posição especifica.
void ODEBody::addForceAtPosition(const ODEVector3 &force, const ODEVector3 &pos)
{
	this->setEnable(true);
	dBodyAddForceAtPos(this->id, (dReal)force[0], (dReal)force[1], (dReal)force[2]
		, (dReal)pos[0], (dReal)pos[1], (dReal)pos[2]);
}



/// Aplica uma força numa posição numa posição relativa ao centro do corpo.
void ODEBody::addForceAtRelativePosition(const ODEVector3 &force, const ODEVector3 &pos)
{
	this->setEnable(true);
	dBodyAddForceAtRelPos(this->id, (dReal)force[0], (dReal)force[1], (dReal)force[2]
		, (dReal)pos[0], (dReal)pos[1], (dReal)pos[2]);
}



/// Aplica uma força relativa ao frame de referência do corpo numa posição especifica.
void ODEBody::addRelativeForceAtPosition(const ODEVector3 &force, const ODEVector3 &pos)
{
	this->setEnable(true);
	dBodyAddRelForceAtPos(this->id, (dReal)force[0], (dReal)force[1], (dReal)force[2]
		, (dReal)pos[0], (dReal)pos[1], (dReal)pos[2]);
}



/// Aplica uma força relativa ao frame de referência do corpo numa posição relativa ao centro do corpo.
void ODEBody::addRelativeForceAtRelativePosition(const ODEVector3 &force, const ODEVector3 &pos)
{
	this->setEnable(true);
	dBodyAddRelForceAtRelPos(this->id, (dReal)force[0], (dReal)force[1], (dReal)force[2]
		, (dReal)pos[0], (dReal)pos[1], (dReal)pos[2]);
}



/// Define se o corpo está activo.
void ODEBody::setEnable(bool enable)
{
	if (enable)
	{
		dBodyEnable(this->id);
	}
	else
	{
		dBodyDisable(this->id);
	}
}



/// Indica se o corpo está activo.
bool ODEBody::isEnabled() const
{
	return (dBodyIsEnabled(this->id) == 1);
}



/// Devolve a identificaçao do corpo.
dBodyID ODEBody::getID() const
{
	return this->id;
}