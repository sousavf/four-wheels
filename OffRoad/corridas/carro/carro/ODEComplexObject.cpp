#include "ODEHeaders.h"

using namespace ODE;

/// Constrói o objecto.
ODEComplexObject::ODEComplexObject(ODEWorld &world)
	:ODEObject(world),space(world, world.getSpace())
{
}



/// Destrói o objecto.
ODEComplexObject::~ODEComplexObject()
{
	while(!this->objects.empty())
	{
		this->objects[0]->~ODESimpleObject();
		this->objects.erase(this->objects.begin());
	}

	while(!this->joints.empty())
	{
		this->joints[0]->~ODEJoint();
		this->joints.erase(this->joints.begin());
	}
}


/// Devolve o espaço em que o objecto está inserido.
const ODESpace& ODEComplexObject::getSpace() const
{
	return this->space;
}



/// Indica se o objecto tem alguma geometria com um id igual a geom1 ou geom2.
bool ODEComplexObject::isAnyOf(const ODEGeometry &geom1, const ODEGeometry &geom2) const
{
	for (int i = 0; i < (int)this->objects.size(); i++)
	{
		if (this->objects[i]->isAnyOf(geom1, geom2))
		{
			return true;
		}
	}

	return false;
}



/// Indica se o objecto tem alguma geometria com um id igual a geom1 ou geom2.
bool ODEComplexObject::isAnyOf(const ODEGeometry *geom1, const ODEGeometry *geom2) const
{
	return isAnyOf(*geom1, *geom2);
}