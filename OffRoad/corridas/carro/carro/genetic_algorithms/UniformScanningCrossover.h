#ifndef UniformScanningCrossover_h
#define UniformScanningCrossover_h

#include "MultiParentCrossover.h"

class UniformScanningCrossover : public MultiParentCrossover
{
	public:
		UniformScanningCrossover();
		UniformScanningCrossover(int parents);
		UniformScanningCrossover(int parents, double probability);

		virtual CrossoverType Type() const;

	protected:
		void Cross(const std::vector< Chromossome > &parents, std::vector< Chromossome > &sons) const;
};

#endif