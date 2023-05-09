#include "ODETestForces.h"
#include <drawstuff/drawstuff.h>

using namespace ODE;

#pragma warning(disable: 4355)

/// Cria o teste.
ODETestForces::ODETestForces()
	:sphere(this->world, this->world.getSpace(), 0.15f, 0.2f)
	, box1(this->world, this->world.getSpace(), 0.01f, ODEVector3(0.35f, 0.35f, 0.35f))
	, box2(this->world, this->world.getSpace(), 0.01f, ODEVector3(0.35f, 0.35f, 0.35f))
	, box3(this->world, this->world.getSpace(), 0.01f, ODEVector3(0.35f, 0.35f, 0.35f))
{
	this->forceAmount = 20;
}



/// Destrói o teste.
ODETestForces::~ODETestForces()
{
}



/// Controla a força da esfera.
void ODETestForces::command(int c)
{
	switch(c)
	{
		case 'a':
			this->force[1] = -this->forceAmount;
			break;

		case 'd':
			this->force[1] = this->forceAmount;
			break;

		case 'w':
			this->force[0] = -this->forceAmount;
			break;

		case 's':
			this->force[0] = this->forceAmount;
			break;

		case 'r':
			this->world.reset();
			break;
	}
}



/// Faz o step.
void ODETestForces::loop()
{
	this->sphere.addForce(force);
	this->force = ODEVector3();
}



/// Desenha.
void ODETestForces::draw()
{
	dVector3 s;

	dsSetColorAlpha(1, 0, 0, 0.75);
	dGeomBoxGetLengths(this->box1.getGeomID(), s);
	dsDrawBox(dGeomGetPosition(this->box1.getGeomID())
		, dGeomGetRotation(this->box1.getGeomID()), s);
	dsDrawBox(dGeomGetPosition(this->box2.getGeomID())
		, dGeomGetRotation(this->box2.getGeomID()), s);
	dsDrawBox(dGeomGetPosition(this->box3.getGeomID())
		, dGeomGetRotation(this->box3.getGeomID()), s);

	dsSetColorAlpha(0, 0, 1, 0.75);
	dsDrawSphere(dGeomGetPosition(this->sphere.getGeomID())
		, dGeomGetRotation(this->sphere.getGeomID()), this->sphere.getRadius());
}



/// Inicia o teste.
void ODETestForces::start()
{
	this->world.addObject(&this->sphere, ODEVector3(0, 0, 1));
	this->world.addObject(&this->box1, ODEVector3(-3, -0.20f, 0.35f));
	this->world.addObject(&this->box2, ODEVector3(-3, 0.20f, 0.35f));
	this->world.addObject(&this->box3, ODEVector3(-3, 0, 0.7f));
}