#ifndef ODETESTTRACK_H
#define ODETESTTRACK_H

#include "ODETestCar.h"
#include "LapCounter.h"

namespace ODE
{
	/// Para testar pista e carro.
	class ODETestTrack : public ODETestCar
	{
	public:
		ODETestTrack();
		~ODETestTrack();

		virtual bool createContact(ODEContact& contact, ODEGeometry* geom1
			, ODEGeometry* geom2);
		virtual void draw();
		virtual void start();

	protected:
		ODETrack *track;
		LapCounter counter;
	};
}

#endif