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



/// Destrói a junta
ODEFixedJoint::~ODEFixedJoint()
{
}



/// Não faz nada porque esta junta não tem parâmetros.
void ODEFixedJoint::setParameter(Parameter p, ODEReal value, int axis)
{
}



/// Devolve 0 porque esta junta não tem parâmetros.
ODEReal ODEFixedJoint::getParameter(Parameter p, int axis) const
{
	return 0;
}



/// Chamar depois de juntar os dois corpos. Lembra a posição e rotação relativa
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