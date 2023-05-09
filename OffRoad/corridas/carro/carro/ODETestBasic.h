#ifndef ODETESTBASIC_H
#define ODETESTBASIC_H

#include "ODETest.h"

namespace ODE
{
	/// Cria uma caixa, uma esfera.
	class ODETestBasic : public ODETest
	{
	public:
		ODETestBasic();
		~ODETestBasic();

		virtual void command(int c);
		virtual void loop();
		virtual void draw();
		virtual void start();

	protected:
		ODEBox box;
		ODESphere sphere;
	};
}

#endif