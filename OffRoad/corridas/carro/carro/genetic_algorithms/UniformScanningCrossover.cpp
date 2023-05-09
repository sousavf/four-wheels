#include "UniformScanningCrossover.h"
#include <vector>

UniformScanningCrossover::UniformScanningCrossover():MultiParentCrossover(2)
{
	this->sons = 2;
}



/// Cria um novo crossover do tipo uniform scanning para parents pais e com probability.
UniformScanningCrossover::UniformScanningCrossover(int parents):MultiParentCrossover(parents)
{
	this->sons = 1;
}


/// Cria um novo crossover do tipo uniform scanning para parents pais e com probability.
UniformScanningCrossover::UniformScanningCrossover(int parents, double probability)
								:MultiParentCrossover(parents, probability)
{
	this->sons = 1;
}



/// Efectua o cruzamento através do método uniform scanning crossover.
void UniformScanningCrossover::Cross(const std::vector< Chromossome > &parents
									, std::vector< Chromossome > &sons) const
{
	std::vector< double > son_genes[1];
	int p;

	for (int i = 0; i < parents[0].Length(); i++)
	{
		p = Math::RandomInt(0, (int)parents.size() - 1);
		son_genes[0].push_back(((Chromossome)parents[p])[i]);
	}
	GenesToChromossomes(son_genes, 1, sons);

	son_genes[0].~vector();
}



Crossover::CrossoverType UniformScanningCrossover::Type() const
{
	return UniformScanning;
}