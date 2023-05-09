#include "stdafx.h"
#include "ODETestJoints.h"
#include <drawstuff/drawstuff.h>

using namespace ODE;

#pragma warning(disable: 4355)

/// Cria o teste.
ODETestJoints::ODETestJoints()
	:box(this->world, this->world.getSpace(), 0.1f, ODEVector3(1.2f, 0.8f, 0.2f))
	, wheelFL(world, world.getSpace(), 0.01f, 0.2f, 0.15f)
	, wheelFR(world, world.getSpace(), 0.01f, 0.2f, 0.15f)
	, wheelBL(world, world.getSpace(), 0.01f, 0.2f, 0.15f)
	, wheelBR(world, world.getSpace(), 0.01f, 0.2f, 0.15f)
	, jointFL(world), jointFR(world), jointBL(world), jointBR(world)
{
	this->speed = 0;
	this->turn = 0;
	this->turnAmount = 0.15f;
	this->speedAmount = 2;
}



/// Destrói o teste.
ODETestJoints::~ODETestJoints()
{
}



/// Controla a velocidade e rotação.
void ODETestJoints::command(int c)
{
	switch(c)
	{
		case 'a':
			if (this->speed < 10)
			{
				this->speed += this->speedAmount;
			}
			break;

		case 'z':
			if (this->speed > 0)
			{
				this->speed -= this->speedAmount;
			}
			break;

		case ',':
			if (this->turn > -0.5)
			{
				this->turn -= this->turnAmount;
			}
			break;

		case '.':
			if (this->turn < 0.5)
			{
				this->turn += this->turnAmount;
			}
			break;

		case ' ':
			this->speed = 0;
			this->turn = 0;
			break;

		case 'r':
			this->speed = 0;
			this->turn = 0;
			this->world.reset();
			break;
	}
}



/// Faz o step.
void ODETestJoints::loop()
{
	this->jointFL.setParameter(ODE::ODEJoint::Velocity, turn - this->jointFL.getAngle1(), 2);
	this->jointFR.setParameter(ODE::ODEJoint::Velocity, turn - this->jointFR.getAngle1(), 2);
	this->jointFL.setParameter(ODE::ODEJoint::Velocity, speed);
	this->jointFR.setParameter(ODE::ODEJoint::Velocity, speed);
	this->jointBL.setParameter(ODE::ODEJoint::Velocity, speed);
	this->jointBR.setParameter(ODE::ODEJoint::Velocity, speed);
}



/// Desenha.
void ODETestJoints::draw()
{
	dVector3 s;

	dsSetColorAlpha(1, 0, 0, 0.75);
	dGeomBoxGetLengths(this->box.getGeomID(), s);
	dsDrawBox(dGeomGetPosition(this->box.getGeomID())
		, dGeomGetRotation(this->box.getGeomID()), s);
	
	dsSetColorAlpha(0, 0, 1, 0.75);
	dsDrawCylinder(dGeomGetPosition(this->wheelFL.getGeomID())
		, dGeomGetRotation(this->wheelFL.getGeomID())
		, this->wheelFL.getLength(), this->wheelFL.getRadius());
	dsDrawCylinder(dGeomGetPosition(this->wheelFR.getGeomID())
		, dGeomGetRotation(this->wheelFR.getGeomID())
		, this->wheelFR.getLength(), this->wheelFR.getRadius());
	dsDrawCylinder(dGeomGetPosition(this->wheelBL.getGeomID())
		, dGeomGetRotation(this->wheelBL.getGeomID())
		, this->wheelBL.getLength(), this->wheelBL.getRadius());
	dsDrawCylinder(dGeomGetPosition(this->wheelBR.getGeomID())
		, dGeomGetRotation(this->wheelBR.getGeomID())
		, this->wheelBR.getLength(), this->wheelBR.getRadius());
}



/// Inicia o teste.
void ODETestJoints::start()
{
	ODEQuaternion rot;
	ODEVector3 size;
	ODEReal length, width, height;

	size = this->box.getSize();
	length = size[1];
	width = size[0];
	height = size[2];
	rot.fromAxisAndAngle(1, 0, 0, 0.5f * M_PI);
	this->world.addObject(this->box, ODEVector3(0, 0, 0.5f * height + 1));
	this->world.addObject(this->wheelFL
		, ODEVector3(-0.4f * width, -0.6f * length, 0.6f * height + 1), rot);
	this->world.addObject(this->wheelFR
		, ODEVector3(-0.4f * width, 0.6f * length, 0.6f * height + 1), rot);
	this->world.addObject(this->wheelBL
		, ODEVector3(0.4f * width, -0.6f * length, 0.6f * height + 1), rot);
	this->world.addObject(this->wheelBR
		, ODEVector3(0.4f * width, 0.6f * length, 0.6f * height + 1), rot);
	this->jointFL.attach(this->box.getBody(), this->wheelFL.getBody());
	this->jointFR.attach(this->box.getBody(), this->wheelFR.getBody());
	this->jointBL.attach(this->box.getBody(), this->wheelBL.getBody());
	this->jointBR.attach(this->box.getBody(), this->wheelBR.getBody());
	this->jointFL.setAnchor(ODEVector3(-0.4f * width, -0.6f * length, 0.6f * height + 1));
	this->jointFR.setAnchor(ODEVector3(-0.4f * width, 0.6f * length, 0.6f * height + 1));
	this->jointBL.setAnchor(ODEVector3(0.4f * width, -0.6f * length, 0.6f * height + 1));
	this->jointBR.setAnchor(ODEVector3(0.4f * width, 0.6f * length, 0.6f * height + 1));
	this->jointFL.setAxis1(ODEVector3(0, 0, 1));
	this->jointFR.setAxis1(ODEVector3(0, 0, 1));
	this->jointBL.setAxis1(ODEVector3(0, 0, 1));
	this->jointBR.setAxis1(ODEVector3(0, 0, 1));
	this->jointFL.setAxis2(ODEVector3(0, 1, 0));
	this->jointFR.setAxis2(ODEVector3(0, 1, 0));
	this->jointBL.setAxis2(ODEVector3(0, 1, 0));
	this->jointBR.setAxis2(ODEVector3(0, 1, 0));
	this->jointFL.setParameter(ODE::ODEJoint::SuspensionERP, 0.2f);
	this->jointFL.setParameter(ODE::ODEJoint::SuspensionCFM, 0.01f);
	this->jointFR.setParameter(ODE::ODEJoint::SuspensionERP, 0.2f);
	this->jointFR.setParameter(ODE::ODEJoint::SuspensionCFM, 0.01f);
	this->jointBL.setParameter(ODE::ODEJoint::SuspensionERP, 0.2f);
	this->jointBL.setParameter(ODE::ODEJoint::SuspensionCFM, 0.01f);
	this->jointBR.setParameter(ODE::ODEJoint::SuspensionERP, 0.2f);
	this->jointBR.setParameter(ODE::ODEJoint::SuspensionCFM, 0.01f);
	
	this->jointFL.setParameter(ODE::ODEJoint::MaximumForce, 1);
	this->jointFL.setParameter(ODE::ODEJoint::MaximumForce, 0.4f, 2);
	this->jointFL.setParameter(ODE::ODEJoint::FudgeFactor, 0.2f);
	this->jointFL.setParameter(ODE::ODEJoint::LowStop, -1, 2);
	this->jointFL.setParameter(ODE::ODEJoint::HighStop, 1, 2);
	this->jointFL.setParameter(ODE::ODEJoint::LowStop, -1, 2);
	this->jointFL.setParameter(ODE::ODEJoint::HighStop, 1, 2);
	
	this->jointFR.setParameter(ODE::ODEJoint::MaximumForce, 1);
	this->jointFR.setParameter(ODE::ODEJoint::MaximumForce, 0.4f, 2);
	this->jointFR.setParameter(ODE::ODEJoint::FudgeFactor, 0.2f);
	this->jointFR.setParameter(ODE::ODEJoint::LowStop, -1, 2);
	this->jointFR.setParameter(ODE::ODEJoint::HighStop, 1, 2);
	this->jointFR.setParameter(ODE::ODEJoint::LowStop, -1, 2);
	this->jointFR.setParameter(ODE::ODEJoint::HighStop, 1, 2);
	
	this->jointBL.setParameter(ODE::ODEJoint::LowStop, 0, 2);
	this->jointBL.setParameter(ODE::ODEJoint::HighStop, 0, 2);
	this->jointBL.setParameter(ODE::ODEJoint::LowStop, 0, 2);
	this->jointBL.setParameter(ODE::ODEJoint::HighStop, 0, 2);
	this->jointBR.setParameter(ODE::ODEJoint::LowStop, 0, 2);
	this->jointBR.setParameter(ODE::ODEJoint::HighStop, 0, 2);
	this->jointBR.setParameter(ODE::ODEJoint::LowStop, 0, 2);
	this->jointBR.setParameter(ODE::ODEJoint::HighStop, 0, 2);
}