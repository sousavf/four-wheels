#ifndef SinglePointCrossover_h
#define SinglePointCrossover_h

#include "Crossover.h"

class SinglePointCrossover : public Crossover
{
	public:
		SinglePointCrossover();
		SinglePointCrossover(double probability);

		virtual CrossoverType Type() const;

	protected:
		void Cross(const std::vector< Chromossome > &parents, std::vector< Chromossome > &sons) const;
};

#endif