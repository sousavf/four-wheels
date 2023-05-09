#include "UniformCrossover.h"

/// Cria um novo crossover do tipo uniform.
UniformCrossover::UniformCrossover():Crossover()
{
}



/// Cria um novo crossover do tipo uniform.
UniformCrossover::UniformCrossover(double probability):Crossover(probability)
{
}


/// Efectua um cruzamento do tipo uniform. Cada um dos genes dos pais tem uma probabilidade
/// de 50% de passar para um dos filhos.
void UniformCrossover::Cross(const std::vector< Chromossome > &parents
									, std::vector< Chromossome > &sons) const
{
	std::vector< double > sons_genes[2];

	for (int i = 0, j, k; i < parents[0].Length(); i++)
	{
		j = (Math::RandomPercentage() > 0.5) ? 0 : 1;
		k = (j == 0) ? 1 : 0;
		sons_genes[j].push_back(((Chromossome)parents[0])[i]);
		sons_genes[k].push_back(((Chromossome)parents[1])[i]);
	}
	GenesToChromossomes(sons_genes, 2, sons);

	for (int i = 0; i < 2; i++)
	{
		sons_genes[i].~vector();
	}
}



Crossover::CrossoverType UniformCrossover::Type() const
{
	return Uniform;
}