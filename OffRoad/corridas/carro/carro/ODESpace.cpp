#include "ODEHeaders.h"

using namespace ODE;

/// Cria um novo espaço.
ODESpace::ODESpace(ODEWorld &world)
{
	this->world = &world;
	this->id = dHashSpaceCreate(0);
	dGeomSetData((dGeomID)this->id, (void*)this);
}



/// Cria um espaço pertencente a outro espaço.
ODESpace::ODESpace(ODEWorld &world, const ODESpace &space)
{
	this->world = &world;
	this->id = dHashSpaceCreate(space.getID());
	dGeomSetData((dGeomID)this->id, (void*)this);
}



/// Destrói o espaço.
ODESpace::~ODESpace()
{
	//dSpaceDestroy(this->id);
}



/// Adiciona a geometria ao espaço.
void ODESpace::add(const ODEGeometry &geom)
{
	dSpaceAdd(this->id, geom.getID());
}



/// Remove a geometria do espaço.
void ODESpace::remove(const ODEGeometry &geom)
{
	dSpaceRemove(this->id, geom.getID());
}



/// Indica se a geometria pertence ao espaço.
bool ODESpace::contains(const ODEGeometry &geom) const
{
	return (dSpaceQuery(this->id, geom.getID()) == 1);
}



/// Indica o número de geometrias pertencentes ao espaço.
int ODESpace::count() const
{
	return dSpaceGetNumGeoms(this->id);
}



/// Devolve a identificação do espaço.
dSpaceID ODESpace::getID() const
{
	return this->id;
}