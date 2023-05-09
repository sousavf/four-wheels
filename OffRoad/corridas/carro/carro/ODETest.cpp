#include "ODETest.h"

using namespace ODE;

#pragma warning(disable: 4355)

/// Cria o teste.
ODETest::ODETest():world(-9.80665f), ground(world, world.getSpace(), ODEVector4(0, 0, 1, 0))
{
}



/// Destrói o teste.
ODETest::~ODETest()
{
}



/// Devolve o mundo.
ODESimulation& ODETest::getWorld()
{
	return this->world;
}



/// Trata dos contactos entreee objectos.
bool ODETest::createContact(ODEContact& contact, ODEGeometry* geom1, ODEGeometry* geom2)
{
	contact.setFrictionMode(ODEContact::BothFrictionPyramids);
	contact.setCoulombFriction(dInfinity, dInfinity);
	contact.setForceDependentSlip(0.15f, 0.15f);
	contact.setSoftness(1, 0.02f);

	return true;
}