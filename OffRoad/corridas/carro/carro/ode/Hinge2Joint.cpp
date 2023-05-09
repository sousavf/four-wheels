#include "Hinge2Joint.h"
#include "World.h"

/// Cria uma nova joint vazia.
Hinge2Joint::Hinge2Joint()
{
}



/// Cria uma nova joint pertencente a world.
Hinge2Joint::Hinge2Joint(World &world)
{
	Init(world);
}



/// Cria uma nova joint pertencente a world.
void Hinge2Joint::Init(World &world)
{
	this->joint = dJointCreateHinge2(world.ID(), 0);
}



/// Destrói a joint.
Hinge2Joint::~Hinge2Joint()
{
}



/// Estabelece os parâmetros para anchor.
void Hinge2Joint::SetAnchor(XYZ xyz)
{
	dJointSetHinge2Anchor(this->joint, (dReal)xyz.x, (dReal)xyz.y, (dReal)xyz.z);
}



/// Estabelece os parâmetros para axis 1 (axis 1 e axis 2 não devem pertencer à mesma linha).
void Hinge2Joint::SetAxis1(XYZ xyz)
{
	dJointSetHinge2Axis1(this->joint, (dReal)xyz.x, (dReal)xyz.y, (dReal)xyz.z);
}



/// Estabelece os parâmetros para axis 2 (axis 1 e axis 2 não devem pertencer à mesma linha).
void Hinge2Joint::SetAxis2(XYZ xyz)
{
	dJointSetHinge2Axis2(this->joint, (dReal)xyz.x, (dReal)xyz.y, (dReal)xyz.z);
}



/// Estabelece o valor de param na joint.
void Hinge2Joint::SetParameter(MotorParameter param, double value)
{
	dJointSetHinge2Param(this->joint, GetODEParameter(param), (dReal) value);
}



/// Devolve o valor do parâmetro especificado.
double Hinge2Joint::GetParameter(MotorParameter param)
{
	return (double) dJointGetHinge2Param(this->joint, GetODEParameter(param));
}



/// Devolve o ângulo da joint.
double Hinge2Joint::GetAngle1()
{
	return (double) dJointGetHinge2Angle1(this->joint);
}



/// Devolve o angle rate do axis 1 da joint.
double Hinge2Joint::GetAngle1Rate()
{
	return (double) dJointGetHinge2Angle1Rate(this->joint);
}



/// Devolve o angle rate do axis 2 da joint.
double Hinge2Joint::GetAngle2Rate()
{
	return (double) dJointGetHinge2Angle2Rate(this->joint);
}