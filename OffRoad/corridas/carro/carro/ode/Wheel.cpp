#include "Wheel.h"
#include "WheelGeometry.h"
#include "World.h"

/// Cria uma nova roda vazia.
Wheel::Wheel()
{
}



/// Constrói uma roda com massa, raio e largura específicas.
Wheel::Wheel(World &world, double mass, double radius, double width)
{
	Init(world, mass, radius, width);
}



/// Constrói uma roda com massa, raio e largura específicas.
void Wheel::Init(World &world, double mass, double radius, double width)
{
	dQuaternion q;
	dMass m;

	Object::Init(world, mass);
	this->mass = mass;
	dQFromAxisAndAngle(q, 0, 1, 0, (dReal) (0.5 * Math::PI));
    dBodySetQuaternion(this->body, q);
    dBodySetGravityMode(this->body, 1);
    dBodySetFiniteRotationMode(this->body, 1);
	dMassSetCylinderTotal(&m, (dReal) mass, 1, (dReal) radius, (dReal) width);
	dBodySetMass(this->body, &m);
	this->geometry = new WheelGeometry(*(world.WorldSpace()), radius, width, Geometry::Black);
	dGeomSetBody(this->geometry->ID(), this->body);
}



/// Destrói a roda.
Wheel::~Wheel()
{
}



/// Prepara a roda para mais uma iteração do ciclo principal do mundo.
void Wheel::Prepare()
{
	Object::Prepare();

	if (dBodyGetNumJoints(this->ID()) > 0)
	{
		dVector3 v;

		dBodySetFiniteRotationMode(this->ID(), 1);
		dJointGetHinge2Axis1(dBodyGetJoint(this->ID(), 0), v);
		dBodySetFiniteRotationAxis(this->ID(), v[0], v[1], v[2]);
	}
}