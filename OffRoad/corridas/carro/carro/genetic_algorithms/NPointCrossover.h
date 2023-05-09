#ifndef NPointCrossover_h
#define NPointCrossover_h

#include "Crossover.h"

class NPointCrossover : public Crossover
{
	friend class SinglePointCrossover;
	friend class TwoPointCrossover;
	friend class DiagonalCrossover;

	public:
		NPointCrossover();
		NPointCrossover(int points);
		NPointCrossover(int points, double probability);

		double GetPoints() const;
		void SetPoints(int value);

		virtual CrossoverType Type() const;
		virtual std::ostream& NPointCrossover::Save(std::ostream& os) const;
		virtual std::istream& NPointCrossover::Load(std::istream& is);

	protected:
		int points;

		void Cross(const std::vector< Chromossome > &parents
					, std::vector< Chromossome > &sons) const;
		static void Cross(const std::vector< Chromossome > &parents
							, std::vector< Chromossome > &sons, int points);
		static std::vector< int > GetBridges(int n, int max);
};

#endif