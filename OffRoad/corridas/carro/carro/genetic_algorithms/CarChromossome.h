#ifndef CarChromossome_h
#define CarChromossome_h

#include "Chromossome.h"
#include <ode/ode.h>

class CarChromossome : public Chromossome
{
	friend class GeneticAlgorithm;

	public:
		CarChromossome();
		CarChromossome(CarChromossome &chromo);
		CarChromossome(double mass, double width, double height, double length, double off_mass, double off_width
	, double off_height, double off_length, double off_x, double off_y, double off_z, double wheelMass
	, double wheelRadius, double wheelWidth, double wheel_x, double wheel_y, double wheel_z, double serp
	, double scfm, double stop_erp, double stop_cfm, double cfm, double mforce, double mforce2, double fudgefactor);

		static const double MAX_MASS;
		static const double MAX_WIDTH;
		static const double MAX_HEIGHT;
		static const double MAX_LENGTH;
		static const double MAX_OFF_MASS;
		static const double MAX_OFF_WIDTH;
		static const double MAX_OFF_HEIGHT;
		static const double MAX_OFF_LENGTH;
		static const double MAX_OFF_X;
		static const double MAX_OFF_Y;
		static const double MAX_OFF_Z;
		static const double MAX_WHEEL_MASS;
		static const double MAX_WHEEL_RADIUS;
		static const double MAX_WHEEL_WIDTH;
		static const double MAX_WHEEL_X;
		static const double MAX_WHEEL_Y;
		static const double MAX_WHEEL_Z;
		static const double MAX_SERP;
		static const double MAX_SCFM;
		static const double MAX_STOP_ERP;
		static const double MAX_STOP_CFM;
		static const double MAX_CFM;
		static const double MAX_M_FORCE;
		static const double MAX_M_FORCE2;
		static const double MAX_FUDGEFACTOR;
		static const double MIN_MASS;
		static const double MIN_WIDTH;
		static const double MIN_HEIGHT;
		static const double MIN_LENGTH;
		static const double MIN_OFF_MASS;
		static const double MIN_OFF_WIDTH;
		static const double MIN_OFF_HEIGHT;
		static const double MIN_OFF_LENGTH;
		static const double MIN_OFF_X;
		static const double MIN_OFF_Y;
		static const double MIN_OFF_Z;
		static const double MIN_WHEEL_MASS;
		static const double MIN_WHEEL_RADIUS;
		static const double MIN_WHEEL_WIDTH;
		static const double MIN_WHEEL_X;
		static const double MIN_WHEEL_Y;
		static const double MIN_WHEEL_Z;
		static const double MIN_SERP;
		static const double MIN_SCFM;
		static const double MIN_STOP_ERP;
		static const double MIN_STOP_CFM;
		static const double MIN_CFM;
		static const double MIN_M_FORCE;
		static const double MIN_M_FORCE2;
		static const double MIN_FUDGEFACTOR;

	protected:
		void Init(double mass, double width, double height, double length, double off_mass, double off_width
	, double off_height, double off_length, double off_x, double off_y, double off_z, double wheelMass
	, double wheelRadius, double wheelWidth, double wheel_x, double wheel_y, double wheel_z, double serp
	, double scfm, double stop_erp, double stop_cfm, double cfm, double mforce, double mforce2, double fudgefactor);
};

#endif
