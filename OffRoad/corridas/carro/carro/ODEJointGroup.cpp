#include "ODEHeaders.h"

using namespace ODE;

/// Cria um grupo de juntas.
ODEJointGroup::ODEJointGroup(ODEWorld &world)
{
	this->world = &world;
	this->id = dJointGroupCreate(0);
}



/// Destr�i o grupo de juntas.
ODEJointGroup::~ODEJointGroup()
{
	dJointGroupDestroy(this->id);
}



/// Esvazia o grupo de juntas. Todas juntas s�o destru�das.
void ODEJointGroup::empty()
{
	dJointGroupEmpty(this->id);
}



/// Devolve a identifica��o.
dJointGroupID ODEJointGroup::getID() const
{
	return this->id;
}