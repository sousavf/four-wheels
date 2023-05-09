#include "TournamentSelection.h"
#include "GeneticAlgorithm.h"
#include "Math.h"
#include <vector>

/// Cria um novo método de selecção com torneios de 2 membros.
TournamentSelection::TournamentSelection()
{
	Init(2);
}



/// Cria um novo método de selecção com torneios de tournamentSize participantes.
TournamentSelection::TournamentSelection(int tournamentSize)
{
	Init(tournamentSize);
}



/// Cria um novo método de selecção com torneios de tournamentSize participantes.
void TournamentSelection::Init(int tournamentSize)
{
	this->tournamentSize = (tournamentSize > 1) ? tournamentSize : 2;
}



/// Selecciona um cromossoma através do método tournament selection.
Chromossome& TournamentSelection::Select(GeneticAlgorithm* ga) const
{
	std::vector< Chromossome > choosen;
	bool found;
	int c, best;

	// escolhe os participantes para o torneio (não repetidos)
	for (int i = 0; i < this->tournamentSize; i++)
	{
		do
		{
			c = Math::RandomInt(0, ga->PopulationSize() - 1);
			found = false;
			
			for (int j = 0; j < (int)choosen.size(); j++)
			{
				if (choosen[j] == (*ga)[c])
				{
					found = true;
					break;
				}
			}
		}
		while (found);

        choosen.push_back((*ga)[c]);        
	}

	// determina o melhor
	for (int i = 0; i < (int)choosen.size(); i++)
	{
		if ( i == 0 || (choosen[i].GetFitness() > choosen[best].GetFitness()) )
		{
            best = i;
		}
	}

	return choosen[best];
}



/// Define o número de pariticpantes em cada torneio. value tem de ser > 1
void TournamentSelection::SetTournamentSize(int value)
{
	if (value > 1)
	{
		this->tournamentSize = value;
	}
}



/// Indica o número de pariticpantes em cada torneio.
int TournamentSelection::GetTournamentSize() const
{
	return this->tournamentSize;
}


