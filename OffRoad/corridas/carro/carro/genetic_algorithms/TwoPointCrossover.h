#ifndef TwoPointCrossover_h
#define TwoPointCrossover_h

#include "Crossover.h"

class TwoPointCrossover : public Crossover
{
	public:
		TwoPointCrossover();
		TwoPointCrossover(double probability);

		virtual CrossoverType Type() const;

	protected:
		void Cross(const std::vector< Chromossome > &parents, std::vector< Chromossome > &sons) const;
};

#endif