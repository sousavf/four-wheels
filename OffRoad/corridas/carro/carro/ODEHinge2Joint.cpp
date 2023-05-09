#include "ODEHeaders.h"

using namespace ODE;

/// Cria uma junta do tipo hinge2.
ODEHinge2Joint::ODEHinge2Joint(ODEWorld &world):ODEJoint(world)
{
	this->id = dJointCreateHinge2(world.getID(), 0);
}

/// Cria uma junta do tipo hinge2.
ODEHinge2Joint::ODEHinge2Joint(ODEWorld &world, const ODEJointGroup &group):ODEJoint(world)
{
	this->id = dJointCreateHinge2(world.getID(), group.getID());
}



/// Destrói a junta.
ODEHinge2Joint::~ODEHinge2Joint()
{
}



/// Define o valor para o parâmetro p no eixo axis.
void ODEHinge2Joint::setParameter(Parameter p, ODEReal value, int axis)
{
	dJointSetHinge2Param(this->id, Param(p, axis), (dReal)value);
}



/// Define a âncora da junta.
void ODEHinge2Joint::setAnchor(const ODEVector3 &axis)
{
	dJointSetHinge2Anchor(this->id, (dReal)axis[0], (dReal)axis[1], (dReal)axis[2]);
}



/// Define o 1º eixo. Não pode ter o mesmo valor do 2º eixo.
void ODEHinge2Joint::setAxis1(const ODEVector3 &axis)
{
	dJointSetHinge2Axis1(this->id, (dReal)axis[0], (dReal)axis[1], (dReal)axis[2]);
}



/// Define o 2º eixo. Não pode ter o mesmo valor do 1º eixo.
void ODEHinge2Joint::setAxis2(const ODEVector3 &axis)
{
	dJointSetHinge2Axis2(this->id, (dReal)axis[0], (dReal)axis[1], (dReal)axis[2]);
}



/// Devolve o valor do parâmetro p no eixo axis.
ODEReal ODEHinge2Joint::getParameter(Parameter p, int axis) const
{
	return (ODEReal)dJointGetHinge2Param(this->id, Param(p, axis));
}



/// Devolve a âncora da junta.
const ODEVector3 ODEHinge2Joint::getAnchor() const
{
	ODEVector3 anchor;
	dVector3 a;

	dJointGetHinge2Anchor(this->id, a);
	anchor = a;

	return anchor;
}



/// Devolve o valor da âncora da junta relativa ao corpo 2.
/// Deverá ser o mesmo valor da âncora1, mas caso haja erros
/// podemos determinar qual é o erro através da diferença nas âncoras.
const ODEVector3 ODEHinge2Joint::getAnchor2() const
{
	ODEVector3 anchor;
	dVector3 a;

	dJointGetHinge2Anchor2(this->id, a);
	anchor = a;

	return anchor;
}



/// Devolve o 1º eixo.
const ODEVector3 ODEHinge2Joint::getAxis1() const
{
	ODEVector3 axis;
	dVector3 a;

	dJointGetHinge2Axis1(this->id, a);
	axis = a;

	return axis;
}



/// Devolve o 2º eixo.
const ODEVector3 ODEHinge2Joint::getAxis2() const
{
	ODEVector3 axis;
	dVector3 a;

	dJointGetHinge2Axis2(this->id, a);
	axis = a;

	return axis;
}



/// Adiciona torques aos corpos ligados pela junta.
void ODEHinge2Joint::addTorques(ODEReal torque1, ODEReal torque2)
{
	dJointAddHinge2Torques(this->id, (dReal)torque1, (dReal)torque2);
}



/// Devolve o ângulo em torno do eixo 1.
ODEReal ODEHinge2Joint::getAngle1() const
{
	return (ODEReal)dJointGetHinge2Angle1(this->id);
}



/// Devolve a derivada do ângulo em torno do eixo 1.
ODEReal ODEHinge2Joint::getAngle1Rate() const
{
	return (ODEReal)dJointGetHinge2Angle1Rate(this->id);
}



/// Devolve o ângulo em torno do eixo 2.
ODEReal ODEHinge2Joint::getAngle2Rate() const
{
	return (ODEReal)dJointGetHinge2Angle2Rate(this->id);
}



/// Devolve o tipo de junta.
ODEJoint::Type ODEHinge2Joint::getType() const
{
	return Hinge2;
}