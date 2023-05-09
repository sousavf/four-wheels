#ifndef MultiParentCrossover_h
#define MultiParentCrossover_h

#include "Crossover.h"

class MultiParentCrossover : public Crossover
{
	public:
		MultiParentCrossover(int parents);
		MultiParentCrossover(int parents, double probability);

		virtual void SetParentsCount(int value);
		virtual CrossoverType Type() const = 0;
};

#endif