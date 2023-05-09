#include "ODEHeaders.h"

using namespace ODE;

/// Constrói o objecto.
ODESimpleObject::ODESimpleObject(ODEWorld &world)
	:ODEObject(world),body(world)
{
	this->geometry = NULL;
}



/// Destrói o objecto.
ODESimpleObject::~ODESimpleObject()
{
	delete this->geometry;
}



/// Define uma posição para o objecto. Deve ser usado para estabelecer
/// as condições iniciais de uma simulação ou para um eventual reset.
/// Para posicionar um objecto devem ser usadas forças.
void ODESimpleObject::setPosition(const ODEVector3 &pos)
{
	this->body.setPosition(pos);
}



/// Define a rotação do objecto. Deve ser usado para estabelecer
/// as condições iniciais de uma simulação ou para um eventual reset.
/// Para rodar um objecto devem ser usadas forças.
void ODESimpleObject::setRotation(const ODEMatrix3 &rot)
{
	this->body.setRotation(rot);
}



/// Define uma orientação para o objecto. Deve ser usado para estabelecer
/// as condições iniciais de uma simulação ou para um eventual reset.
/// Para rodar um objecto devem ser usadas forças.
void ODESimpleObject::setQuaternion(const ODEQuaternion &orientation)
{
	this->body.setQuaternion(orientation);
}



/// Define a velocidade linear do objecto. Só deve ser usado em casos em que queremos
/// fazer um reset, por exemplo. Não se deve forçar uma velocidade específica num objecto,
/// apenas aplicar forças.
void ODESimpleObject::setLinearVelocity(const ODEVector3 &vel)
{
	this->body.setLinearVelocity(vel);
}



/// Define a velocidade angular do objecto. Só deve ser usado em casos em que queremos
/// fazer um reset, por exemplo. Não se deve forçar uma velocidade específica num objecto,
/// apenas aplicar forças.
void ODESimpleObject::setAngularVelocity(const ODEVector3 &vel)
{
	this->body.setAngularVelocity(vel);
}



/// Define as forças acumuladas no objecto. É útil para situações em que queremos
/// retirar as forças aplicadas a um objecto (para reset). Para aplicarmos uma força
/// a um objecto devemos usar os métodos addForce...
void ODESimpleObject::setForce(const ODEVector3 &force)
{
	this->body.setForce(force);
}



/// Define as forças angulares acumuladas no objecto. É útil para situações em que queremos
/// retirar as forças aplicadas a um objecto (para reset). Para aplicarmos uma força angular
/// a um objecto devemos usar os métodos addTorque...
void ODESimpleObject::setTorque(const ODEVector3 &torque)
{
	this->body.setTorque(torque);
}



/// Define a categoria do objecto. Pode ser usado para fazer com que
/// certas categorias de objectos colidam e outras não.
void ODESimpleObject::setCategoryBits(unsigned long bits)
{
	this->geometry->setCategoryBits(bits);
}



/// Define com o que é que o objecto colide.
void ODESimpleObject::setCollideBits(unsigned long bits)
{
	this->geometry->setCollideBits(bits);
}



/// Devolve a posição do objecto.
const ODEVector3 ODESimpleObject::getPosition() const
{
	return this->body.getPosition();
}



/// Devolve a rotação do objecto.
const ODEMatrix3 ODESimpleObject::getRotation() const
{
	return this->body.getRotation();
}



/// Devolve a orientação do objecto.
const ODEQuaternion ODESimpleObject::getQuaternion() const
{
	return this->body.getQuaternion();
}



/// Devolve a velocidade linear do objecto.
const ODEVector3 ODESimpleObject::getLinearVelocity() const
{
	return this->body.getLinearVelocity();
}



/// Devolve a velocidade angular do objecto.
const ODEVector3 ODESimpleObject::getAngularVelocity() const
{
	return this->body.getAngularVelocity();
}



/// Devolve um vector com as forças acumuladas no objecto.
const ODEVector3 ODESimpleObject::getForce() const
{
	return this->body.getForce();
}



/// Devolve um vector com as forças angulares acumuladas no objecto.
const ODEVector3 ODESimpleObject::getTorque() const
{
	return this->body.getTorque();
}



/// Devolve a categoria do objecto.
unsigned long ODESimpleObject::getCategoryBits() const
{
	return this->geometry->getCategoryBits();
}



/// Devolve os bits de colisão do objecto.
unsigned long ODESimpleObject::getCollideBits() const
{
	return this->geometry->getCollideBits();
}



/// Devolve a massa do objecto
ODEReal ODESimpleObject::getMass()
{
	return this->body.getMass().getValue();
}



/// Aplica uma força ao objecto.
void ODESimpleObject::addForce(const ODEVector3 &force)
{
	this->body.addForce(force);
}



/// Aplica uma força angular.
void ODESimpleObject::addTorque(const ODEVector3 &torque)
{
	this->body.addTorque(torque);
}



/// Aplica força relativa ao frame de referência do objecto.
void ODESimpleObject::addRelativeForce(const ODEVector3 &force)
{
	this->body.addRelativeForce(force);
}



/// Aplica uma força angular relativa ao frame de referência do objecto.
void ODESimpleObject::addRelativeTorque(const ODEVector3 &torque)
{
	this->body.addRelativeTorque(torque);
}



/// Aplica uma força numa posição especifica.
void ODESimpleObject::addForceAtPosition(
	const ODEVector3 &force, const ODEVector3 &pos)
{
	this->body.addForceAtPosition(force, pos);
}



/// Aplica uma força numa posição numa posição relativa ao centro do objecto.
void ODESimpleObject::addForceAtRelativePosition(
	const ODEVector3 &force, const ODEVector3 &pos)
{
	this->body.addForceAtRelativePosition(force, pos);
}



/// Aplica uma força relativa ao frame de referência do objecto numa posição especifica.
void ODESimpleObject::addRelativeForceAtPosition(
	const ODEVector3 &force, const ODEVector3 &pos)
{
	this->body.addRelativeForceAtPosition(force, pos);
}



/// Aplica uma força relativa ao frame de referência do objecto
/// numa posição relativa ao centro do objecto.
void ODESimpleObject::addRelativeForceAtRelativePosition(
	const ODEVector3 &force, const ODEVector3 &pos)
{
	this->body.addRelativeForceAtRelativePosition(force, pos);
}



/// Define se o objecto está activo.
void ODESimpleObject::setEnable(bool enable)
{
	this->body.setEnable(enable);
	this->geometry->setEnable(enable);
}



/// Indica se o objecto está activo.
bool ODESimpleObject::isEnabled() const
{
	return this->body.isEnabled();
}



/// Devolve o espaço em que o objecto se encontra associada
/// ou NULL se não estiver em nenhum espaço.
const ODESpace& ODESimpleObject::getSpace() const
{
	return this->geometry->getSpace();
}



/// Devolve a identificação da geometria.
dGeomID ODESimpleObject::getGeomID() const
{
	return this->geometry->getID();
}



/// Devolve a identificação do corpo.
dBodyID ODESimpleObject::getBodyID() const
{
	return this->body.getID();
}



/// Devolve o corpo.
ODEBody& ODESimpleObject::getBody()
{
	return this->body;
}



/// Devolve a geometria.
const ODEGeometry& ODESimpleObject::getGeometry() const
{
	return *(this->geometry);
}



/// Indica se a geometria do objecto é alguma das 2 passadas como argumento.
bool ODESimpleObject::isAnyOf(const ODEGeometry &geom1, const ODEGeometry &geom2) const
{
	return this->geometry->isAnyOf(geom1, geom2);
}



/// Indica se a geometria do objecto é alguma das 2 passadas como argumento.
bool ODESimpleObject::isAnyOf(const ODEGeometry *geom1, const ODEGeometry *geom2) const
{
	return isAnyOf(*geom1, *geom2);
}