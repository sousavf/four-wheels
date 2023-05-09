#ifndef DiagonalCrossover_h
#define DiagonalCrossover_h

#include "MultiParentCrossover.h"

class DiagonalCrossover : public MultiParentCrossover
{
	public:
		DiagonalCrossover();
		DiagonalCrossover(int parents);
		DiagonalCrossover(int parents, double probability);
		
		void SetParentsCount(int value);
		virtual CrossoverType Type() const;

		static bool Check();

	protected:
		void Cross(const std::vector< Chromossome > &parents, std::vector< Chromossome > &sons) const;
};

#endif