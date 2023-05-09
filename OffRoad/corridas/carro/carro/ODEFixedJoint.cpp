#include "ODEHeaders.h"

using namespace ODE;

/// Cria uma nova junta do tipo fixed.
ODEFixedJoint::ODEFixedJoint(ODEWorld &world):ODEJoint(world)
{
	this->id = dJointCreateFixed(world.getID(), 0);
}



/// Cria uma nova junta do tipo fixed.
ODEFixedJoint::ODEFixedJoint(ODEWorld &world, const ODEJointGroup &group):ODEJoint(world)
{
	this->id = dJointCreateFixed(world.getID(), group.getID());
}



/// Destr�i a junta
ODEFixedJoint::~ODEFixedJoint()
{
}



/// N�o faz nada porque esta junta n�o tem par�metros.
void ODEFixedJoint::setParameter(Parameter p, ODEReal value, int axis)
{
}



/// Devolve 0 porque esta junta n�o tem par�metros.
ODEReal ODEFixedJoint::getParameter(Parameter p, int axis) const
{
	return 0;
}



/// Chamar depois de juntar os dois corpos. Lembra a posi��o e rota��o relativa
/// entre else.
void ODEFixedJoint::setFixed()
{
	dJointSetFixed(this->id);
}



/// Devolve o tipo de junta.
ODEJoint::Type ODEFixedJoint::getType() const
{
	return Fixed;
}