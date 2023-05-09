#ifndef ODETESTFORCES_H
#define ODETESTFORCES_H

#include "ODETest.h"

namespace ODE
{
	/// Cria 3 caixas, uma esfera e podemos controlar a esfera.
	class ODETestForces : public ODETest
	{
	public:
		ODETestForces();
		~ODETestForces();

		virtual void command(int c);
		virtual void loop();
		virtual void draw();
		virtual void start();

	protected:
		ODEBox box1;
		ODEBox box2;
		ODEBox box3;
		ODESphere sphere;
		ODEVector3 force;
		ODEReal forceAmount;
	};
}

#endif
