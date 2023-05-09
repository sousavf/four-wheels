#ifndef RoulletteWheelSelection_h
#define RoulletteWheelSelection_h

#include <vector>
#include "Selection.h"

class RoulletteWheelSelection : public Selection
{
	public:
		virtual Chromossome& Select(GeneticAlgorithm* ga) const;
		int Select(std::vector< Chromossome > &chromossomes, double totalFitness) const;
};

#endif