#include "ODEHeaders.h"

using namespace ODE;

/// Cria um objecto
ODEObject::ODEObject(ODEWorld &world)
{
	this->world = &world;
}



/// Destr�i o objecto.
ODEObject::~ODEObject()
{
}



/// Devolve o mundo a que pertence o objecto.
ODEWorld& ODEObject::getWorld()
{
	return *(this->world);
}