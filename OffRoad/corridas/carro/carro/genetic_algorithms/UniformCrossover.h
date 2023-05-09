#ifndef UniformCrossover_h
#define UniformCrossover_h

#include "Crossover.h"

class UniformCrossover : public Crossover
{
	public:
		UniformCrossover();
		UniformCrossover(double probability);

		virtual CrossoverType Type() const;

	protected:
		void Cross(const std::vector< Chromossome > &parents, std::vector< Chromossome > &sons) const;
};

#endif