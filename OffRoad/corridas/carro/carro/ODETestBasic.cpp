#include "ODETestBasic.h"
#include <drawstuff/drawstuff.h>

using namespace ODE;

#pragma warning(disable: 4355)

/// Cria o teste.
ODETestBasic::ODETestBasic()
	:box(this->world, this->world.getSpace(), 0.1f, ODEVector3(0.8f, 1.4f, 0.1f))
	, sphere(this->world, this->world.getSpace(), 0.1f, 0.2f)
{
}



/// Destrói o teste.
ODETestBasic::~ODETestBasic()
{
}



/// Faz reset caso pressione-se 'r'.
void ODETestBasic::command(int c)
{
	switch(c)
	{
		case 'r':
			this->world.reset();
			break;
	}
}



/// Não faz nada.
void ODETestBasic::loop()
{
}



/// Desenha.
void ODETestBasic::draw()
{
	dVector3 s;

	dsSetColorAlpha(1, 0, 0, 0.75);
	dGeomBoxGetLengths(this->box.getGeomID(), s);
	dsDrawBox(dGeomGetPosition(this->box.getGeomID())
		, dGeomGetRotation(this->box.getGeomID()), s);

	dsSetColorAlpha(0, 0, 1, 0.75);
	dsDrawSphere(dGeomGetPosition(this->sphere.getGeomID())
		, dGeomGetRotation(this->sphere.getGeomID()), this->sphere.getRadius());
}



/// Inicia o teste.
void ODETestBasic::start()
{
	ODEQuaternion rot;

	this->world.addObject(&this->sphere, ODEVector3(0, 0, 1));
	rot.fromAxisAndAngle(0, 0, 1, 0.25 * M_PI);
	this->world.addObject(&this->box, ODEVector3(0, -0.1F, 2), rot);
}