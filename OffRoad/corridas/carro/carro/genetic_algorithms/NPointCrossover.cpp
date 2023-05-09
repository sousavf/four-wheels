#include "NPointCrossover.h"
#include <algorithm>
#include <vector>

/// Cria um crossover do tipo NPoint.
NPointCrossover::NPointCrossover():Crossover()
{
	this->points = 1;
}



/// Cria um crossover do tipo NPoint.
NPointCrossover::NPointCrossover(int points):Crossover()
{
	this->points = (points > 0) ? points : 1;
}



/// Cria um crossover do tipo NPoint.
NPointCrossover::NPointCrossover(int points, double probability):Crossover(probability)
{
	this->points = (points > 0) ? points : 1;
}



/// Devolve o número de pontos que usa no crossover.
double NPointCrossover::GetPoints() const
{
	return this->points;
}



/// Estabelece o número de pontos que usa no crossover. value tem de ser > 0
void NPointCrossover::SetPoints(int value)
{
	if (value > 0)
	{
		this->points = value;
	}
}



/// Efectua um cruzamento através do método n-point usando o número de pontos especificado.
void NPointCrossover::Cross(const std::vector< Chromossome > &parents
							, std::vector< Chromossome > &sons) const
{
	Cross(parents, sons, this->points);
}



/// Efectua um cruzamento através do método n-point usando points pontos especificado.
void NPointCrossover::Cross(const std::vector< Chromossome > &parents
							, std::vector< Chromossome > &sons, int points)
{
	std::vector< double > sons_genes[2];
	std::vector< int > bridges;
	int j = 0, k = 0, l = 1;

	bridges = GetBridges(points, parents[0].Length() - 1);
	bridges.push_back(parents[0].Length() - 1);	// para copiar os genes até ao fim

	// copia genes dos pais para os filhos respectivos trocando em pontes
	for (int i = 0; i < (int)bridges.size(); i++)
	{
        for ( ; j <= bridges[i]; j++)
		{
			sons_genes[k].push_back(((Chromossome)parents[0])[j]);
			sons_genes[l].push_back(((Chromossome)parents[1])[j]);
		}
		k = (k == 0) ? 1 : 0;
		l = (l == 0) ? 1 : 0;
	}
	GenesToChromossomes(sons_genes, 2, sons);
}



/// Devolve um vector com n pontos ordenados aleatórios de 0 a max não repetidos.
std::vector< int > NPointCrossover::GetBridges(int n, int max)
{
	std::vector< int > bridges;
	bool exists;
	int r;

	for (int i = 0; i < n; i++)
	{
		do
		{
			r = Math::RandomInt(0, max);
			exists = false;
			
			for (int j = 0; j < (int)bridges.size(); j++)
			{
				if (bridges[j] == r)
				{
					exists = true;
					break;
				}
			}
		}
		while (exists);

		bridges.push_back(r);
		
	}
	sort(bridges.begin(), bridges.end());

	return bridges;
}



/// Grava o crossover para o stream.
std::ostream& NPointCrossover::Save(std::ostream& os) const
{
	os << this->points << std::endl;

	return os;
}



/// Lê o crossover do stream.
std::istream& NPointCrossover::Load(std::istream& is)
{
	is >> this->points;

	return is;
}



/// Indica o tipo de crossover.
Crossover::CrossoverType NPointCrossover::Type() const
{
	return NPoint;
}