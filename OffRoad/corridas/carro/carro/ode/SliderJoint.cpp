#include "SliderJoint.h"
#include "World.h"

/// Cria uma nova joint vazia.
SliderJoint::SliderJoint()
{
}



/// Cria uma nova joint pertencente a world.
SliderJoint::SliderJoint(World &world)
{
	Init(world);
}



/// Cria uma nova joint pertencente a world.
void SliderJoint::Init(World &world)
{
	this->joint = dJointCreateSlider(world.ID(), 0);
}



/// Destr�i a joint.
SliderJoint::~SliderJoint()
{
}



/// Estabelece o axis do slider.
void SliderJoint::SetAxis(XYZ xyz)
{
	dJointSetSliderAxis(this->joint, (dReal)xyz.x, (dReal)xyz.y, (dReal)xyz.z);
}




/// Devolve a posi��o linear do slider.
double SliderJoint::GetPosition() const
{
	return dJointGetSliderPosition(this->joint);
}



/// Devolve a derivada no tempo da posi��o linear do slider.
double SliderJoint::GetPositionRate() const
{
	return dJointGetSliderPositionRate(this->joint);
}



/// Estabelece o valor de param na joint.
void SliderJoint::SetParameter(MotorParameter param, double value)
{
	dJointSetSliderParam(this->joint, GetODEParameter(param), (dReal) value);
}



/// Devolve o valor do par�metro especificado.
double SliderJoint::GetParameter(MotorParameter param)
{
	return (double) dJointGetSliderParam(this->joint, GetODEParameter(param));
}