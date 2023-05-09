#include "ODEHeaders.h"

using namespace ODE;

/// Constr�i o objecto.
ODESimpleObject::ODESimpleObject(ODEWorld &world)
	:ODEObject(world),body(world)
{
	this->geometry = NULL;
}



/// Destr�i o objecto.
ODESimpleObject::~ODESimpleObject()
{
	delete this->geometry;
}



/// Define uma posi��o para o objecto. Deve ser usado para estabelecer
/// as condi��es iniciais de uma simula��o ou para um eventual reset.
/// Para posicionar um objecto devem ser usadas for�as.
void ODESimpleObject::setPosition(const ODEVector3 &pos)
{
	this->body.setPosition(pos);
}



/// Define a rota��o do objecto. Deve ser usado para estabelecer
/// as condi��es iniciais de uma simula��o ou para um eventual reset.
/// Para rodar um objecto devem ser usadas for�as.
void ODESimpleObject::setRotation(const ODEMatrix3 &rot)
{
	this->body.setRotation(rot);
}



/// Define uma orienta��o para o objecto. Deve ser usado para estabelecer
/// as condi��es iniciais de uma simula��o ou para um eventual reset.
/// Para rodar um objecto devem ser usadas for�as.
void ODESimpleObject::setQuaternion(const ODEQuaternion &orientation)
{
	this->body.setQuaternion(orientation);
}



/// Define a velocidade linear do objecto. S� deve ser usado em casos em que queremos
/// fazer um reset, por exemplo. N�o se deve for�ar uma velocidade espec�fica num objecto,
/// apenas aplicar for�as.
void ODESimpleObject::setLinearVelocity(const ODEVector3 &vel)
{
	this->body.setLinearVelocity(vel);
}



/// Define a velocidade angular do objecto. S� deve ser usado em casos em que queremos
/// fazer um reset, por exemplo. N�o se deve for�ar uma velocidade espec�fica num objecto,
/// apenas aplicar for�as.
void ODESimpleObject::setAngularVelocity(const ODEVector3 &vel)
{
	this->body.setAngularVelocity(vel);
}



/// Define as for�as acumuladas no objecto. � �til para situa��es em que queremos
/// retirar as for�as aplicadas a um objecto (para reset). Para aplicarmos uma for�a
/// a um objecto devemos usar os m�todos addForce...
void ODESimpleObject::setForce(const ODEVector3 &force)
{
	this->body.setForce(force);
}



/// Define as for�as angulares acumuladas no objecto. � �til para situa��es em que queremos
/// retirar as for�as aplicadas a um objecto (para reset). Para aplicarmos uma for�a angular
/// a um objecto devemos usar os m�todos addTorque...
void ODESimpleObject::setTorque(const ODEVector3 &torque)
{
	this->body.setTorque(torque);
}



/// Define a categoria do objecto. Pode ser usado para fazer com que
/// certas categorias de objectos colidam e outras n�o.
void ODESimpleObject::setCategoryBits(unsigned long bits)
{
	this->geometry->setCategoryBits(bits);
}



/// Define com o que � que o objecto colide.
void ODESimpleObject::setCollideBits(unsigned long bits)
{
	this->geometry->setCollideBits(bits);
}



/// Devolve a posi��o do objecto.
const ODEVector3 ODESimpleObject::getPosition() const
{
	return this->body.getPosition();
}



/// Devolve a rota��o do objecto.
const ODEMatrix3 ODESimpleObject::getRotation() const
{
	return this->body.getRotation();
}



/// Devolve a orienta��o do objecto.
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



/// Devolve um vector com as for�as acumuladas no objecto.
const ODEVector3 ODESimpleObject::getForce() const
{
	return this->body.getForce();
}



/// Devolve um vector com as for�as angulares acumuladas no objecto.
const ODEVector3 ODESimpleObject::getTorque() const
{
	return this->body.getTorque();
}



/// Devolve a categoria do objecto.
unsigned long ODESimpleObject::getCategoryBits() const
{
	return this->geometry->getCategoryBits();
}



/// Devolve os bits de colis�o do objecto.
unsigned long ODESimpleObject::getCollideBits() const
{
	return this->geometry->getCollideBits();
}



/// Devolve a massa do objecto
ODEReal ODESimpleObject::getMass()
{
	return this->body.getMass().getValue();
}



/// Aplica uma for�a ao objecto.
void ODESimpleObject::addForce(const ODEVector3 &force)
{
	this->body.addForce(force);
}



/// Aplica uma for�a angular.
void ODESimpleObject::addTorque(const ODEVector3 &torque)
{
	this->body.addTorque(torque);
}



/// Aplica for�a relativa ao frame de refer�ncia do objecto.
void ODESimpleObject::addRelativeForce(const ODEVector3 &force)
{
	this->body.addRelativeForce(force);
}



/// Aplica uma for�a angular relativa ao frame de refer�ncia do objecto.
void ODESimpleObject::addRelativeTorque(const ODEVector3 &torque)
{
	this->body.addRelativeTorque(torque);
}



/// Aplica uma for�a numa posi��o especifica.
void ODESimpleObject::addForceAtPosition(
	const ODEVector3 &force, const ODEVector3 &pos)
{
	this->body.addForceAtPosition(force, pos);
}



/// Aplica uma for�a numa posi��o numa posi��o relativa ao centro do objecto.
void ODESimpleObject::addForceAtRelativePosition(
	const ODEVector3 &force, const ODEVector3 &pos)
{
	this->body.addForceAtRelativePosition(force, pos);
}



/// Aplica uma for�a relativa ao frame de refer�ncia do objecto numa posi��o especifica.
void ODESimpleObject::addRelativeForceAtPosition(
	const ODEVector3 &force, const ODEVector3 &pos)
{
	this->body.addRelativeForceAtPosition(force, pos);
}



/// Aplica uma for�a relativa ao frame de refer�ncia do objecto
/// numa posi��o relativa ao centro do objecto.
void ODESimpleObject::addRelativeForceAtRelativePosition(
	const ODEVector3 &force, const ODEVector3 &pos)
{
	this->body.addRelativeForceAtRelativePosition(force, pos);
}



/// Define se o objecto est� activo.
void ODESimpleObject::setEnable(bool enable)
{
	this->body.setEnable(enable);
	this->geometry->setEnable(enable);
}



/// Indica se o objecto est� activo.
bool ODESimpleObject::isEnabled() const
{
	return this->body.isEnabled();
}



/// Devolve o espa�o em que o objecto se encontra associada
/// ou NULL se n�o estiver em nenhum espa�o.
const ODESpace& ODESimpleObject::getSpace() const
{
	return this->geometry->getSpace();
}



/// Devolve a identifica��o da geometria.
dGeomID ODESimpleObject::getGeomID() const
{
	return this->geometry->getID();
}



/// Devolve a identifica��o do corpo.
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



/// Indica se a geometria do objecto � alguma das 2 passadas como argumento.
bool ODESimpleObject::isAnyOf(const ODEGeometry &geom1, const ODEGeometry &geom2) const
{
	return this->geometry->isAnyOf(geom1, geom2);
}



/// Indica se a geometria do objecto � alguma das 2 passadas como argumento.
bool ODESimpleObject::isAnyOf(const ODEGeometry *geom1, const ODEGeometry *geom2) const
{
	return isAnyOf(*geom1, *geom2);
}