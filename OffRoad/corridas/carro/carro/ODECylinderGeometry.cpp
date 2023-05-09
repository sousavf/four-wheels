#include "ODEHeaders.h"

using namespace ODE;

/// Cria uma geometria de um cilindro em world, em space com radius e length.
ODECylinderGeometry::ODECylinderGeometry(ODEWorld &world, const ODESpace &space, ODEReal radius, ODEReal length
						 , const ODEContactDefinition &contactDef)
						:ODEGeometry(world, contactDef)
{
	this->id = dCreateCCylinder(space.getID(), (dReal)radius, (dReal)length);
	this->setData();
}



/// Destrói a geometria.
ODECylinderGeometry::~ODECylinderGeometry()
{
}



/// Define o raio do cilindro.
void ODECylinderGeometry::setRadius(ODEReal radius)
{
	dReal radius2, length;

	dGeomCCylinderGetParams(this->id, &radius2, &length); 
	dGeomCCylinderSetParams(this->id, (dReal)radius, (dReal)length);
}



/// Define o comprimento do cilindro.
void ODECylinderGeometry::setLength(ODEReal length)
{
	dReal radius, length2;

	dGeomCCylinderGetParams(this->id, &radius, &length2); 
	dGeomCCylinderSetParams(this->id, (dReal)radius, (dReal)length);
}



/// Devolve o raio do cilindro.
ODEReal ODECylinderGeometry::getRadius() const
{
	dReal radius, length;

	dGeomCCylinderGetParams(this->id, &radius, &length); 

	return (ODEReal)radius;
}



/// Devolve o comprimento do cilindro.
ODEReal ODECylinderGeometry::getLength() const
{
	dReal radius, length;

	dGeomCCylinderGetParams(this->id, &radius, &length); 

	return (ODEReal)length;
}