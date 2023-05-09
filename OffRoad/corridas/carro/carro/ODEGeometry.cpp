#include "ODEHeaders.h"

using namespace ODE;

/// Cria uma geometria.
ODEGeometry::ODEGeometry(ODEWorld &world, const ODEContactDefinition &contactDef)
	:contactDefinition(contactDef)
{
	this->world = &world;
	this->id = NULL;
}



/// Destr�i a geometria.
ODEGeometry::~ODEGeometry()
{
	dGeomDestroy(this->id);
}



/// Define o corpo associado � geometria.
void ODEGeometry::setBody(const ODEBody &body)
{
	dGeomSetBody(this->id, body.getID());
}



/// Define a posi��o da geometria.
void ODEGeometry::setPosition(const ODEVector3 &pos)
{
	dGeomSetPosition(this->id, (dReal)pos[0], (dReal)pos[1], (dReal)pos[2]);
}



/// Define a rota��o da geometria.
void ODEGeometry::setRotation(const ODEMatrix3 &rot)
{
	dMatrix3 r;

	for (int i = 0; i < 12; i++)
	{
		r[i] = (dReal)rot[i];
	}
	dGeomSetRotation(this->id, r);
}



/// Define a orienta��o da geometria atrav�s de um quaternion.
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
/// certas categorias de geometrias colidam e outras n�o.
void ODEGeometry::setCategoryBits(unsigned long bits)
{
	dGeomSetCategoryBits(this->id, bits);
}



/// Define com o que � que a geometria colide.
void ODEGeometry::setCollideBits(unsigned long bits)
{
	dGeomSetCollideBits(this->id, bits);
}



/// Devolve o corpo associado � geometria.
ODEBody* ODEGeometry::getBody() const
{
	const dBodyID body = dGeomGetBody(this->id);

	return (ODEBody*)dBodyGetData(body);
}



/// Devolve a posi��o da geometria.
const ODEVector3 ODEGeometry::getPosition() const
{
	ODEVector3 position;
	const dReal* p;

	p = dGeomGetPosition(this->id);
	position = p;

	return position;
}



/// Devolve a orienta��o da geometria num quaternion.
const ODEQuaternion ODEGeometry::getQuaternion() const
{
	ODEQuaternion quaternion;
	dQuaternion o;

	dGeomGetQuaternion(this->id, o);
	quaternion = o;

	return quaternion;
}



/// Devolve a rota��o da geometria num vector de 12 posi��es.
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



/// Devolve os bits de colis�o da geometria.
unsigned long ODEGeometry::getCollideBits() const
{
	return dGeomGetCollideBits(this->id);
}



/// Define se a geometria est� activa.
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



/// Indica se a geometria est� activa. 
bool ODEGeometry::isEnabled() const
{
	return (dGeomIsEnabled(this->id) == 1);
}



/// Devolve a identifica��o da geometria.
dGeomID ODEGeometry::getID() const
{
	return this->id;
}



/// Devolve o espa�o em que a geometria se encontra associada
/// ou NULL se n�o estiver em nenhum espa�o.
ODESpace& ODEGeometry::getSpace()
{
	dSpaceID space;

	space = dGeomGetSpace(this->id);

	return *((ODESpace*)dGeomGetData(this->id));
}



/// Devolve as defini��es do contacto.
const ODEContactDefinition& ODEGeometry::getContactDefinition() const
{
	return this->contactDefinition;
}



/// Indica se a geometria tem um corpo associado.
bool ODEGeometry::hasBody() const
{
	return (dGeomGetBody(this->id) != 0);
}



/// Associa este objecto � geometria.
void ODEGeometry::setData()
{
	dGeomSetData(this->id, (void*)this);
}



/// Indica se a geometria correspondente a um dos ids passados por par�metro
bool ODEGeometry::isAnyOf(const ODEGeometry &geom1, const ODEGeometry &geom2) const
{
	return ( (*this == geom1) || (*this == geom2) );
}



/// Indica se a geometria correspondente a um dos ids passados por par�metro
bool ODEGeometry::isAnyOf(const ODEGeometry *geom1, const ODEGeometry *geom2) const
{
	return isAnyOf(*geom1, *geom2);
}



/// Indica se uma geometria � igual a outra comparando o ID.
bool ODEGeometry::operator == (const ODEGeometry &geom) const
{
	return (this->id == geom.getID());
}