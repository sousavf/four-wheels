#ifndef WorldChromossome_h
#define WorldChromossome_h

#include "Chromossome.h"
#include <ode/ode.h>

class WorldChromossome : public Chromossome
{
	friend class GeneticAlgorithm;

	public:
		WorldChromossome();
		WorldChromossome(WorldChromossome &chromo);
		WorldChromossome(double gravity, double angularDampening, double linearDampening, double aerodynamic
				, double mu, double mu2, double slip1, double slip2, double soft_erp, double soft_cfm);

		static const double MAX_GRAVIDADE;
		static const double MAX_AERODYNAMIC;
		static const double MAX_ANGULARDAMPENING;
		static const double MAX_LINEARDAMPENING;
		static const double MAX_MU;
		static const double MAX_MU2;
		static const double MAX_SLIP1;
		static const double MAX_SLIP2;
		static const double MAX_SOFT_ERP;
		static const double MAX_SOFT_CFM;

		static const double MIN_GRAVIDADE;
		static const double MIN_AERODYNAMIC;
		static const double MIN_ANGULARDAMPENING;
		static const double MIN_LINEARDAMPENING;
		static const double MIN_MU;
		static const double MIN_MU2;
		static const double MIN_SLIP1;
		static const double MIN_SLIP2;
		static const double MIN_SOFT_ERP;
		static const double MIN_SOFT_CFM;

	protected:
		void Init(double gravity, double angularDampening, double linearDampening, double aerodynamic
				, double mu, double mu2, double slip1, double slip2, double soft_erp, double soft_cfm);
};

#endif
