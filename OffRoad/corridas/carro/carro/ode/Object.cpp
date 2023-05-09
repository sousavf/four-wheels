#include "Object.h"
#include "World.h"

/// Cria um novo objecto vazio.
Object::Object()
{
}



/// Cria um novo corpo em world com mass e coloca-o nas coordenadas 0, 0, 0.
Object::Object(World &world, double mass)
{
	Init(world, mass);
}



/// Cria um novo objecto em world com mass, em position e com rotation.
Object::Object(World &world, double mass, XYZ position, XYZ rotation)
{
	Init(world, mass, position, rotation);
}




// Destrói o objecto
Object::~Object()
{
	if (this->body != NULL)
	{
		dBodyDestroy(this->body);
		this->geometry->~Geometry();
		this->body = NULL;
	}
}



/// Define as características do objecto.
void Object::Init(World &world, double mass, XYZ position, XYZ rotation)
{
	dMatrix3 R;
	dReal x, y, z;

	this->body = dBodyCreate(world.ID());
	dBodySetPosition(this->body, (dReal) position.x, (dReal) position.y, (dReal) position.z);
	dBodySetLinearVel(this->body, 0.0, 0.0, 0.0);
	x = (dReal) (rotation.x / 180.0);
	y = (dReal) (rotation.y / 180.0);
	z = (dReal) (rotation.z / 180.0);
	dRFromAxisAndAngle(R, x, y, z, 180);
	dBodySetRotation(this->body, R);
	this->mass = mass;
	this->bounce = false;
}



/// Define as características do objecto.
void Object::Init(World &world, double mass)
{
	XYZ position, rotation;

	position.x = 0;
	position.y = 0;
	position.z = 0;

	rotation.x = 0;
	rotation.y = 0;
	rotation.z = 0;

	Init(world, mass, position, rotation);
}



/// Estabelece se o objecto "salta"
void Object::SetBounce(bool boolean)
{
	this->bounce = boolean;
}



/// Aplica uma força de forma que o objecto vai para a direita
void Object::Right(Intensity force)
{
	ApplyForce(force, 0, 0);
}



/// Aplica uma força de forma que o objecto vai para a esquerda
void Object::Left(Intensity force)
{
	ApplyForce(-force, 0, 0);
}



/// Aplica uma força de forma que o objecto vai para cima
void Object::Up(Intensity force)
{
	ApplyForce(0, 0, force);
}



/// Aplica uma força de forma que o objecto vai para baixo
void Object::Down(Intensity force)
{
	ApplyForce(0, 0, -force);
}



/// Aplica uma força de forma que o objecto vai para a frente.
void Object::Front(Intensity force)
{
	ApplyForce(0, force, 0);
}



/// Aplica uma força de forma que o objecto vai para trás.
void Object::Back(Intensity force)
{
	ApplyForce(0, -force, 0);
}



/// Aplica uma força ao objecto com a intensidade especificada para cada coordenada.
void Object::ApplyForce(double x, double y, double z)
{
	dBodyAddForce(this->body, (dReal) x, (dReal) y, (dReal) z);
}



/// Aplica um torque ao objecto com a intensidade especificada para cada coordenada.
void Object::ApplyTorque(double x, double y, double z)
{
	dBodyAddTorque(this->body, (dReal) x, (dReal) y, (dReal) z);
}



/// Devolve a massa do oObjecto.
double Object::GetMass()
{
	return this->mass;
}



/// Devolve a geometria do objecto.
Geometry * Object::Geometry() const
{
	return this->geometry;
}



/// Coloca o objecto na sua posição, rotação e cor inicial.
void Object::Reset()
{
	dBodySetLinearVel(this->body, 0.0, 0.0, 0.0);
	dBodySetAngularVel(this->body, 0.0, 0.0, 0.0);
	this->geometry->Reset();
}



/// Indica se foi tocado por algum objecto.
bool Object::WasTouched() const
{
	return Geometry()->WasTouched();
}



/// Devolve True se este objecto tocou em object na última iteração do mundo.
bool Object::Touched(Object& object) const
{
	return Touched(*(object.Geometry()));
}



/// Devolve True se este objecto tocou em geometry na última iteração do mundo.
bool Object::Touched(::Geometry &geometry) const
{
	return Geometry()->Touched(geometry.ID());
}



/// Devolve a identificação deste objecto.
dBodyID Object::ID()
{
	return this->body;
}



/// Devolve o valor de bounce, indicando se o objecto faz bounce.
bool Object::GetBounce()
{
	return this->bounce;
}



/// Prepara o objecto para mais uma iteração do ciclo principal do mundo.
void Object::Prepare()
{
	this->Geometry()->Prepare();
}



/// Define se o corpo se encontra activo.
void Object::SetEnable(bool value)
{
	if (value == true)
	{
		dBodyEnable(this->body);
	}
	else
	{
		dBodyDisable(this->body);
	}
}



/// Indica se o corpo se encontra activo.
bool Object::GetEnable() const
{
	return (dBodyIsEnabled(this->body) == 0 ? false : true);
}