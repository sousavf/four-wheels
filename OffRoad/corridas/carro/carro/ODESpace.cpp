#include "ODEHeaders.h"

using namespace ODE;

/// Cria um novo espa�o.
ODESpace::ODESpace(ODEWorld &world)
{
	this->world = &world;
	this->id = dHashSpaceCreate(0);
	dGeomSetData((dGeomID)this->id, (void*)this);
}



/// Cria um espa�o pertencente a outro espa�o.
ODESpace::ODESpace(ODEWorld &world, const ODESpace &space)
{
	this->world = &world;
	this->id = dHashSpaceCreate(space.getID());
	dGeomSetData((dGeomID)this->id, (void*)this);
}



/// Destr�i o espa�o.
ODESpace::~ODESpace()
{
	//dSpaceDestroy(this->id);
}



/// Adiciona a geometria ao espa�o.
void ODESpace::add(const ODEGeometry &geom)
{
	dSpaceAdd(this->id, geom.getID());
}



/// Remove a geometria do espa�o.
void ODESpace::remove(const ODEGeometry &geom)
{
	dSpaceRemove(this->id, geom.getID());
}



/// Indica se a geometria pertence ao espa�o.
bool ODESpace::contains(const ODEGeometry &geom) const
{
	return (dSpaceQuery(this->id, geom.getID()) == 1);
}



/// Indica o n�mero de geometrias pertencentes ao espa�o.
int ODESpace::count() const
{
	return dSpaceGetNumGeoms(this->id);
}



/// Devolve a identifica��o do espa�o.
dSpaceID ODESpace::getID() const
{
	return this->id;
}