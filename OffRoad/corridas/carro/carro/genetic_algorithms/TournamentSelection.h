#ifndef TournamentSelection_h
#define TournamentSelection_h

#include <vector>
#include "Selection.h"

class TournamentSelection : public Selection
{
	public:
		TournamentSelection();
		TournamentSelection(int tournamentSize);

		Chromossome& Select(GeneticAlgorithm* ga) const;
		void SetTournamentSize(int value);
		int GetTournamentSize() const;

	protected:
		int tournamentSize;

		void Init(int tournamentSize);
};

#endif