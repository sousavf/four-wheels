#include "RankSelection.h"
#include "GeneticAlgorithm.h"
#include <algorithm>
#include <math.h>

/// Escolhe um cromossoma através do método Rank selection.
Chromossome& RankSelection::Select(GeneticAlgorithm* ga) const
{
	std::vector< Chromossome > chromossomesOrdered, chromossomesRank;
	int totalFitness = 0, index;

	chromossomesOrdered = ga->GetChromossomes();
	sort(chromossomesOrdered.begin(), chromossomesOrdered.end(), Lower);

	for (int i = 0; i < ga->PopulationSize(); i++)
	{
		chromossomesRank.push_back(Chromossome((*ga)[i]));
		chromossomesRank[i].SetFitness(IndexOf(chromossomesRank[i]
									, chromossomesOrdered, 0, ga->PopulationSize() - 1));
	}

	for (int i = 0; i < ga->PopulationSize(); i++)
	{
		totalFitness += i;
	}
	index = RoulletteWheelSelection::Select(chromossomesRank, totalFitness - 1);

	return (*ga)[index];
}



/// Indica se c1 é menor que c2.
bool RankSelection::Lower(Chromossome &c1, Chromossome &c2)
{
   return c1 < c2;
}



/// Indica o índice de chromossome em chromossomes efectuando uma pesquisa binária.
int RankSelection::IndexOf(Chromossome &chromossome, std::vector< Chromossome > &chromossomes
																			, int left, int right)
{
	int mid;

    if (right < left)
	{
		printf("Erro right < left");
        return -1;
	}
    mid = (int)floor( (right - left) * 0.5 ) + left;

    if (chromossome > chromossomes[mid])
	{
		return IndexOf(chromossome, chromossomes, mid + 1, right);
	}
    else if (chromossome < chromossomes[mid])
	{
        return IndexOf(chromossome, chromossomes, left, mid - 1);
	}
    else
	{
        return mid;
	}
}