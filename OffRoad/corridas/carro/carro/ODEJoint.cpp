#include "ODEHeaders.h"

using namespace ODE;

/// Cria uma nova junta.
ODEJoint::ODEJoint(ODEWorld &world)
{
	this->world = &world;
	this->id = NULL;
}



/// Destr�i a junta. Se a junta pertencer a algum grupo de juntas ent�o n�o � destru�da
/// e � preciso destruir o grupo primeiro.
ODEJoint::~ODEJoint()
{
	dJointDestroy(this->id);
}



/// Liga os dois corpos atrav�s da junta.
void ODEJoint::attach(const ODEBody &body1, const ODEBody &body2)
{
    dJointAttach(this->id, body1.getID(), body2.getID());
}



/// Desliga a junta dos objectos a que possa estar junta.
void ODEJoint::detach()
{
	dJointAttach(this->id, 0, 0);
}



/// Indica se os dois corpos est�o ligados por qualquer junta.
bool ODEJoint::areConnected(const ODEBody &body1, const ODEBody &body2)
{
	return (dAreConnected(body1.getID(), body2.getID()) == 1);
}



/// Indica se os corpos est�o juntos por um tipo de junta excluindo o tipo t.
bool ODEJoint::areConnectedExcluding(const ODEBody &body1, const ODEBody &body2
											, Type t)
{
	return (dAreConnectedExcluding(body1.getID(), body2.getID(), (int)t) == 1);
}



/// Devolve o primeiro corpo ligado � junta.
ODEBody& ODEJoint::getBody1()
{
	return getBody(0);
}



/// Devolve o segundo corpo ligado � junta.
ODEBody& ODEJoint::getBody2()
{
	return getBody(1);
}



/// Devolve o corpo correspondente a index que se encontra ligado � junta.
/// 0 corresponde ao body1 que foi ligado � junta e 1 corresponde ao body2.
ODEBody& ODEJoint::getBody(int index)
{
	ODEBody* body;
	dBodyID b;
	
	b = dJointGetBody(this->id, index);
	body = (ODEBody*)dBodyGetData(b);
	
	return *body;
}



/// Devolve a identifica��o da junta.
dJointID ODEJoint::getID() const
{
	return this->id;
}



/// Devolve o valor inteiro correspondente ao par�metro p
/// no eixo axis.
int ODEJoint::Param(Parameter p, int axis)
{
	return ((int)p) + dParamGroup * (axis - 1);
}