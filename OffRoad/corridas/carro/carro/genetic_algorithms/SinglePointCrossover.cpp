#include "SinglePointCrossover.h"
#include "NPointCrossover.h"

/// Cria um novo crossover do tipo single point.
SinglePointCrossover::SinglePointCrossover():Crossover()
{
}



/// Cria um novo crossover do tipo single point.
SinglePointCrossover::SinglePointCrossover(double probability):Crossover(probability)
{
}


/// Efectua um cruzamento do tipo single point, em que se escolhe um ponto entre cada
/// pai e é copiado o material genético de cada um dos pais para um dos filhos, até 
/// esse ponto. Chegando ao ponto, trocam, passando cada filho a receber de outro pai.
void SinglePointCrossover::Cross(const std::vector< Chromossome > &parents
									, std::vector< Chromossome > &sons) const
{
	NPointCrossover::Cross(parents, sons, 1);
}



Crossover::CrossoverType SinglePointCrossover::Type() const
{
	return SinglePoint;
}