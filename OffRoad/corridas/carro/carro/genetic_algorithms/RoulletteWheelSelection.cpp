#include "RoulletteWheelSelection.h"
#include "GeneticAlgorithm.h"
#include "Math.h"

/// Escolhe um cromossoma de ga através do método Roullette Wheel Selection.
Chromossome& RoulletteWheelSelection::Select(GeneticAlgorithm* ga) const
{
	int index = Select(ga->GetChromossomes(), ga->TotalFitness());

	return (*ga)[index];
}



/// Devolve o index relativo a um cromossoma escolhido através do método Roullette Wheel Selection.
int RoulletteWheelSelection::Select(std::vector< Chromossome > &chromossomes
										, double totalFitness) const
{
	double slice, fitness_so_far;
	int i;

	slice = Math::RandomPercentage() * totalFitness;
	fitness_so_far = 0;
	i = 0;
	
	while ( (fitness_so_far < slice) && (i < (int)chromossomes.size()) )
	{
		fitness_so_far += chromossomes[i].GetFitness();
		i++;
	}
	i = (i == 0) ? 1 : i;	// se i = 0, pomos i = 1 para na linha a seguir não devolver negativo.

	return i - 1;
}