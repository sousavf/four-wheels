#include "MultiParentCrossover.h"

/// Cria um novo crossover do tipo multi-parent.
MultiParentCrossover::MultiParentCrossover(int parents):Crossover()
{
	this->parents = (parents > 1) ? parents : 2;
}



/// Cria um novo crossover do tipo multi-parent.
MultiParentCrossover::MultiParentCrossover(int parents, double probability):Crossover(probability)
{
	this->parents = (parents > 1) ? parents : 2;
}



/// Define o número de pais que entram no crossover. value tem de ser > 1.
void MultiParentCrossover::SetParentsCount(int value)
{
	if (value > 1)
	{
		this->parents = value;
	}
}
