#include "FixedJoint.h"

/// Cria uma nova joint vazia.
FixedJoint::FixedJoint()
{
}



/// Cria uma nova joint pertencente a world.
FixedJoint::FixedJoint(World &world)
{
	Init(world);
}



/// Cria uma nova joint pertencente a world.
void FixedJoint::Init(World &world)
{
	this->joint = dJointCreateFixed(world.ID(), 0);
}



/// Destr�i a joint.
FixedJoint::~FixedJoint()
{
}



/// Fixa a joint para manter a posi��o e orienta��o relativa dos 2 corpos a que est� ligada.
void FixedJoint::SetFixed()
{
	dJointSetFixed(this->joint);
}