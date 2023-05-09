#include "DiagonalCrossover.h"
#include "NPointCrossover.h"

/// Cria um multi-parent crossover do tipo diagonal.
DiagonalCrossover::DiagonalCrossover():MultiParentCrossover(2)
{
	this->sons = this->parents;
}



/// Cria um multi-parent crossover do tipo diagonal.
DiagonalCrossover::DiagonalCrossover(int parents):MultiParentCrossover(parents)
{
	this->sons = this->parents;
}



/// Cria um multi-parent crossover do tipo diagonal.
DiagonalCrossover::DiagonalCrossover(int parents, double probability)
						:MultiParentCrossover(parents, probability)
{
	this->sons = this->parents;
}



/// Define o número de pais que entram no crossover. value tem de ser > 1.
void DiagonalCrossover::SetParentsCount(int value)
{
	if (value > 1)
	{
		this->parents = value;
		this->sons = value;
	}
}



/// Efectua o cruzamento através do método diagonal crossover.
void DiagonalCrossover::Cross(const std::vector< Chromossome > &parents
							, std::vector< Chromossome > &sons) const
{
	std::vector< double > *sons_genes;
	std::vector< int > bridges;

	sons_genes = new std::vector< double >[this->sons];
	bridges = NPointCrossover::GetBridges(this->parents - 1, parents[0].Length() - 1);
	bridges.push_back(parents[0].Length() - 1);

	for (int i = 0; i < (int)bridges.size(); i++)
	{
        for (int j = 0, l = i; j < this->sons; j++, l++)
		{
			if (l >= this->parents)
			{
				l = 0;
			}

			for (int k = (i == 0 ? 0 : bridges[i - 1] + 1); k <= bridges[i]; k++)
			{
				sons_genes[j].push_back(((Chromossome)parents[l])[k]);
			}
		}
	}
	GenesToChromossomes(sons_genes, this->sons, sons);

	for (int i = 0; i < this->sons; i++)
	{
		sons_genes[i].~vector();
	}
	delete[] sons_genes;
}



/// Indica o tipo de crossover.
Crossover::CrossoverType DiagonalCrossover::Type() const
{
	return Diagonal;
}



/// Testa a validade deste tipo de cruzamento.
bool DiagonalCrossover::Check()
{
	DiagonalCrossover cross = DiagonalCrossover(3, 100);
	std::vector< Chromossome > parents, sons;
	int k, p;

	parents.push_back(Chromossome(5));
	parents.push_back(Chromossome(5));
	parents.push_back(Chromossome(5));
	
	for (int i = 0, j = 0, k = 0; i < 15; i++, j++)
	{
		if ( (i % 5 == 0) && (i > 0) )
		{
			k++;
			j = 0;
		}
		parents[k][j] = i;
	}

	/****************************
	* parents[0] = 0, 1, 2, 3, 4
	* parents[1] = 5, 6, 7, 8, 9
	* parents[2] = 10, 11, 12, 13, 14
	****************************/

	cross.Cross(parents, sons);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (sons[i][0] == parents[j][0])
			{
				for (k = 0, p = 0; k < 5; k++)
				{
					if (sons[i][k] != parents[j][k])
					{
						if (j == 0) j = 1;
						else if (j == 1) j = 2;
						else if (j == 2) j = 0;

						p++;
						k--;

						if (p == 3)
						{
							if (p < 4)
							{
								return false;
							}
							break;
						}
					}
				}
				break;
			}
		}
	}

	return true;
}