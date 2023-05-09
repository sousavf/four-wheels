#ifndef RankWheelSelection_h
#define RankWheelSelection_h

#include "RoulletteWheelSelection.h"

class RankSelection : public RoulletteWheelSelection
{
	public:
		Chromossome& Select(GeneticAlgorithm* ga) const;

	protected:
		static bool RankSelection::Lower(Chromossome &c1, Chromossome &c2);
		static int IndexOf(Chromossome &chromossome, std::vector< Chromossome > &chromossomes
																			, int left, int right);
};

#endif