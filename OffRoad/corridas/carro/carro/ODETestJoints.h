#ifndef ODETESTJOINTS_H
#define ODETESTJOINTS_H

#include "ODETest.h"

namespace ODE
{
	/// Cria 3 caixas, uma esfera e podemos controlar a esfera.
	class ODETestJoints : public ODETest
	{
	public:
		ODETestJoints();
		~ODETestJoints();

		virtual void command(int c);
		virtual void loop();
		virtual void draw();
		virtual void start();

	protected:
		ODEBox box;
		ODECylinder wheelFL;
		ODECylinder wheelFR;
		ODECylinder wheelBL;
		ODECylinder wheelBR;
		ODEReal speed;
		ODEReal turn;
		ODEReal turnAmount;
		ODEReal speedAmount;
		ODEHinge2Joint jointFL;
		ODEHinge2Joint jointFR;
		ODEHinge2Joint jointBL;
		ODEHinge2Joint jointBR;
	};
}

#endif