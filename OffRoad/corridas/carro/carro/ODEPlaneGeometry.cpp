#include "ODEHeaders.h"

using namespace ODE;

/// Cria a geometria de um plano.
ODEPlaneGeometry::ODEPlaneGeometry(ODEWorld &world, const ODESpace &space, const ODEVector4 &p)
	:ODEGeometry(world)
{
	ODEVector4 p2(p);

	this->id = dCreatePlane(space.getID(), (dReal)p2[0], (dReal)p2[1], (dReal)p2[2], (dReal)p2[3]);
	this->setData();
}



/// Destrói o plano.
ODEPlaneGeometry::~ODEPlaneGeometry()
{
}



/// Define os parâmetros do plano.
void ODEPlaneGeometry::setParams(const ODEVector4 &p)
{
	ODEVector4 p2(p);

	dGeomPlaneSetParams(this->id, (dReal)p2[0], (dReal)p2[1], (dReal)p2[2], (dReal)p2[3]);
}



/// Não faz nada.
void ODEPlaneGeometry::setPosition(const ODEVector3 &pos)
{
}



/// Não faz nada.
void ODEPlaneGeometry::setRotation(const ODEMatrix3 &rot)
{
}



/// Não faz nada.
void ODEPlaneGeometry::setQuaternion(const ODEQuaternion &orientation)
{
}



/// Devolve as definições do plano.
const ODEVector4 ODEPlaneGeometry::getParams() const
{
	ODEVector4 params;
	dVector4 v;

	dGeomPlaneGetParams(this->id, v);
	params = v;

	return params;
}



/// Devolve vector vazio.
const ODEVector3 ODEPlaneGeometry::getPosition() const
{
	return ODEVector3();
}



/// Devolve quaternion vazio.
const ODEQuaternion ODEPlaneGeometry::getQuaternion() const
{
	return ODEQuaternion();
}



/// Devolve matriz vazia.
const ODEMatrix3 ODEPlaneGeometry::getRotation() const
{
	return ODEMatrix3();
}