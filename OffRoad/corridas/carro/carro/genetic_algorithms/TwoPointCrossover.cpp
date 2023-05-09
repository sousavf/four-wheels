#include "TwoPointCrossover.h"
#include "NPointCrossover.h"

/// Cria um novo crossover do tipo 2-point.
TwoPointCrossover::TwoPointCrossover():Crossover()
{
}



/// Cria um novo crossover do tipo 2-point.
TwoPointCrossover::TwoPointCrossover(double probability):Crossover(probability)
{
}


/// Efectua um cruzamento do tipo 2-point. Em vez de usarmos uma ponte, usamos 2.
void TwoPointCrossover::Cross(const std::vector< Chromossome > &parents
									, std::vector< Chromossome > &sons) const
{
	NPointCrossover::Cross(parents, sons, 2);
}



Crossover::CrossoverType TwoPointCrossover::Type() const
{
	return TwoPoint;
}