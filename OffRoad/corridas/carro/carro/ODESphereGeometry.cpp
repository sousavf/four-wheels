#include "ODEHeaders.h"

using namespace ODE;

/// Cria uma geometria de esfera pertencente a world, em space e com radius.
ODESphereGeometry::ODESphereGeometry(ODEWorld &world, const ODESpace &space, ODEReal radius
									 , const ODEContactDefinition &contactDef)
									 :ODEGeometry(world, contactDef)
{
	this->id = dCreateSphere(space.getID(), (dReal)radius);
	this->setData();
}



/// Destrói a esfera.
ODESphereGeometry::~ODESphereGeometry()
{
}



/// Define o raio da esfera.
void ODESphereGeometry::setRadius(ODEReal radius)
{
	dGeomSphereSetRadius(this->id, (dReal)radius);
}



/// Devolve o raio da esfera.
ODEReal ODESphereGeometry::getRadius() const
{
	return (ODEReal)dGeomSphereGetRadius(this->id);
}