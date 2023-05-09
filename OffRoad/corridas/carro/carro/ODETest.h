#ifndef ODETEST_H
#define ODETEST_H

#include "ODERequirements.h"
#include "ODEHeaders.h"

namespace ODE
{
	/// Classe para ser usada em testes.
	class ODETest
	{
	public:
		ODETest();
		~ODETest();

		virtual bool createContact(ODEContact& contact, ODEGeometry* geom1
			, ODEGeometry* geom2);
		virtual void command(int c) = 0;
		virtual void loop() = 0;
		virtual void draw() = 0;
		virtual void start() = 0;
		ODESimulation& getWorld();

	protected:
		ODESimulation world;
		ODEPlaneGeometry ground;
	};
}

#endif