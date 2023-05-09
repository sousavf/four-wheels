#include "ODEHeaders.h"

using namespace ODE;

/// Criar uma junta do tipo slider.
ODESliderJoint::ODESliderJoint(ODEWorld &world):ODEJoint(world)
{
	this->id = dJointCreateSlider(world.getID(), 0);
}



/// Criar uma junta do tipo slider.
ODESliderJoint::ODESliderJoint(ODEWorld &world, const ODEJointGroup &group):ODEJoint(world)
{
	this->id = dJointCreateSlider(world.getID(), group.getID());
}



/// Destrói a junta.
ODESliderJoint::~ODESliderJoint()
{
}



/// Define o parâmetro p da junta com o valor value no eixo axis.
void ODESliderJoint::setParameter(Parameter p, ODEReal value, int axis)
{
	dJointSetSliderParam(this->id, Param(p, axis), (dReal)value);
}



/// Define o eixo da junta.
void ODESliderJoint::setAxis(const ODEVector3 &axis)
{
	ODEVector3 axis2(axis);

	dJointSetSliderAxis(this->id, (dReal)axis2[0], (dReal)axis2[1], (dReal)axis2[2]);
}



/// Devolve o valor do parâmetro o para o eixo axis.
ODEReal ODESliderJoint::getParameter(Parameter p, int axis) const
{
	return (ODEReal)dJointGetSliderParam(this->id, Param(p, axis));
}



/// Devolve o eixo.
const ODEVector3& ODESliderJoint::getAxis()
{
	dVector3 a;

	dJointGetSliderAxis(this->id, a);
	this->axis = a;

	return this->axis;
}



/// Adiciona uma força à junta.
void ODESliderJoint::addForce(ODEReal force)
{
	dJointAddSliderForce(this->id, (dReal)force);
}



/// Devolve o tipo de junta.
ODEJoint::Type ODESliderJoint::getType() const
{
	return Slider;
}



/// Devolve a posição linear do slider.
ODEReal ODESliderJoint::getPosition() const
{
	return (ODEReal)dJointGetSliderPosition(this->id);
}



/// Devolve a derivada no tempo da posição linear do slider.
ODEReal ODESliderJoint::getPositionRate() const
{
	return (ODEReal)dJointGetSliderPositionRate(this->id);
}