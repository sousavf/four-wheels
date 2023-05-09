#include "ODEHeaders.h"

using namespace ODE;

/// Cria a geometria de uma caixa pertencente a world, no espaço space e com tamanho size.
ODEBoxGeometry::ODEBoxGeometry(ODEWorld &world, const ODESpace &space, const ODEVector3 &size
   , const ODEContactDefinition &contactDef)
	:ODEGeometry(world, contactDef)
{
	ODEVector3 size2;

	size2 = size;
	this->id = dCreateBox(space.getID(), (dReal)size2[0], (dReal)size2[1], (dReal)size2[2]);
	this->setData();
}



/// Destrói a geometria.
ODEBoxGeometry::~ODEBoxGeometry()
{
}



/// Define o tamanho da geometria.
void ODEBoxGeometry::setSize(const ODEVector3 &size)
{
	ODEVector3 size2(size);

	dGeomBoxSetLengths(this->id, (dReal)size2[0], (dReal)size2[1], (dReal)size2[2]);
}



/// Devolve o tamanho da geometria.
const ODEVector3 ODEBoxGeometry::getSize() const
{
	ODEVector3 size;
	dVector3 l;

	dGeomBoxGetLengths(this->id, l);
	size = l;

	return size;
}