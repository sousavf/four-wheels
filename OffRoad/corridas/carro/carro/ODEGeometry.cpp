#include "ODEHeaders.h"

using namespace ODE;

/// Cria uma geometria.
ODEGeometry::ODEGeometry(ODEWorld &world, const ODEContactDefinition &contactDef)
	:contactDefinition(contactDef)
{
	this->world = &world;
	this->id = NULL;
}



/// Destrói a geometria.
ODEGeometry::~ODEGeometry()
{
	dGeomDestroy(this->id);
}



/// Define o corpo associado à geometria.
void ODEGeometry::setBody(const ODEBody &body)
{
	dGeomSetBody(this->id, body.getID());
}



/// Define a posição da geometria.
void ODEGeometry::setPosition(const ODEVector3 &pos)
{
	dGeomSetPosition(this->id, (dReal)pos[0], (dReal)pos[1], (dReal)pos[2]);
}



/// Define a rotação da geometria.
void ODEGeometry::setRotation(const ODEMatrix3 &rot)
{
	dMatrix3 r;

	for (int i = 0; i < 12; i++)
	{
		r[i] = (dReal)rot[i];
	}
	dGeomSetRotation(this->id, r);
}



/// Define a orientação da geometria através de um quaternion.
void ODEGeometry::setQuaternion(const ODEQuaternion &orientation)
{
	dQuaternion q;

	q[0] = (dReal)orientation[0];
	q[1] = (dReal)orientation[1];
	q[2] = (dReal)orientation[2];
	q[3] = (dReal)orientation[3];
	dGeomSetQuaternion(this->id, q);
}



/// Define a categoria da geometria. Pode ser usado para fazer com que
/// certas categorias de geometrias colidam e outras não.
void ODEGeometry::setCategoryBits(unsigned long bits)
{
	dGeomSetCategoryBits(this->id, bits);
}



/// Define com o que é que a geometria colide.
void ODEGeometry::setCollideBits(unsigned long bits)
{
	dGeomSetCollideBits(this->id, bits);
}



/// Devolve o corpo associado à geometria.
ODEBody* ODEGeometry::getBody() const
{
	const dBodyID body = dGeomGetBody(this->id);

	return (ODEBody*)dBodyGetData(body);
}



/// Devolve a posição da geometria.
const ODEVector3 ODEGeometry::getPosition() const
{
	ODEVector3 position;
	const dReal* p;

	p = dGeomGetPosition(this->id);
	position = p;

	return position;
}



/// Devolve a orientação da geometria num quaternion.
const ODEQuaternion ODEGeometry::getQuaternion() const
{
	ODEQuaternion quaternion;
	dQuaternion o;

	dGeomGetQuaternion(this->id, o);
	quaternion = o;

	return quaternion;
}



/// Devolve a rotação da geometria num vector de 12 posições.
const ODEMatrix3 ODEGeometry::getRotation() const
{
	ODEMatrix3 rotation;
	const dReal* rot = dGeomGetRotation(this->id);
	rotation = rot;

	return rotation;
}



/// Devolve a categoria da geometria.
unsigned long ODEGeometry::getCategoryBits() const
{
	return dGeomGetCategoryBits(this->id);
}



/// Devolve os bits de colisão da geometria.
unsigned long ODEGeometry::getCollideBits() const
{
	return dGeomGetCollideBits(this->id);
}



/// Define se a geometria está activa.
void ODEGeometry::setEnable(bool enable)
{
	if (enable)
	{
		dGeomEnable(this->id);
	}
	else
	{
		dGeomDisable(this->id);
	}
}



/// Indica se a geometria está activa. 
bool ODEGeometry::isEnabled() const
{
	return (dGeomIsEnabled(this->id) == 1);
}



/// Devolve a identificação da geometria.
dGeomID ODEGeometry::getID() const
{
	return this->id;
}



/// Devolve o espaço em que a geometria se encontra associada
/// ou NULL se não estiver em nenhum espaço.
ODESpace& ODEGeometry::getSpace()
{
	dSpaceID space;

	space = dGeomGetSpace(this->id);

	return *((ODESpace*)dGeomGetData(this->id));
}



/// Devolve as definições do contacto.
const ODEContactDefinition& ODEGeometry::getContactDefinition() const
{
	return this->contactDefinition;
}



/// Indica se a geometria tem um corpo associado.
bool ODEGeometry::hasBody() const
{
	return (dGeomGetBody(this->id) != 0);
}



/// Associa este objecto à geometria.
void ODEGeometry::setData()
{
	dGeomSetData(this->id, (void*)this);
}



/// Indica se a geometria correspondente a um dos ids passados por parâmetro
bool ODEGeometry::isAnyOf(const ODEGeometry &geom1, const ODEGeometry &geom2) const
{
	return ( (*this == geom1) || (*this == geom2) );
}



/// Indica se a geometria correspondente a um dos ids passados por parâmetro
bool ODEGeometry::isAnyOf(const ODEGeometry *geom1, const ODEGeometry *geom2) const
{
	return isAnyOf(*geom1, *geom2);
}



/// Indica se uma geometria é igual a outra comparando o ID.
bool ODEGeometry::operator == (const ODEGeometry &geom) const
{
	return (this->id == geom.getID());
}