#include "ODEHeaders.h"

using namespace ODE;

/// Cria um grupo de juntas.
ODEJointGroup::ODEJointGroup(ODEWorld &world)
{
	this->world = &world;
	this->id = dJointGroupCreate(0);
}



/// Destrói o grupo de juntas.
ODEJointGroup::~ODEJointGroup()
{
	dJointGroupDestroy(this->id);
}



/// Esvazia o grupo de juntas. Todas juntas são destruídas.
void ODEJointGroup::empty()
{
	dJointGroupEmpty(this->id);
}



/// Devolve a identificação.
dJointGroupID ODEJointGroup::getID() const
{
	return this->id;
}