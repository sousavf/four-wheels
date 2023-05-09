#include "Crossover.h"
#include "UniformCrossover.h"
#include "UniformScanningCrossover.h"
#include "TwoPointCrossover.h"
#include "NPointCrossover.h"
#include "DiagonalCrossover.h"
#include "SinglePointCrossover.h"
#include "../ode/Auxiliary.h"

/// Cria uma nova função de crossover com os valroes por defeito.
Crossover::Crossover()
{
	Init(2, 2, 0.7);
}



/// Cria uma nova função de crossover para 2 pais e 2 filhos e com probability.
Crossover::Crossover(double probability)
{
	Init(2, 2, probability);
}



/// Cria uma nova função de crossover para um número específico de pais e de filhos e com probability.
void Crossover::Init(int parents, int sons, double probability)
{
	this->parents = (parents > 1) ? parents : 2;
	this->sons = (sons > 0) ? sons : 2;
	this->probability = probability;
}



/// Destrói esta função de crossover.
Crossover::~Crossover()
{
}



/// Devolve o número de pais que entram no crossover.
int Crossover::GetParentsCount() const
{
	return this->parents;
}



/// Devolve o número de filhos que entram no crossover.
int Crossover::GetSonsCount() const
{
	return this->sons;
}



/// Devolve a probabilidade de efectuar um crossover.
double Crossover::GetProbability() const
{
	return this->probability;
}



/// Define a probabilidade de efectuar um crossover. value tem de ser >= 0.
void Crossover::SetProbability(double value)
{
	if (value >= 0)
	{
		this->probability = value;
	}
}



/// Tendo em conta o número de pais para que está configurado, efectua um crossover
/// para os pais em parents (ignora o resto dos elementos se existirem a mais e 
/// ignora a operação se houverem pais a menos) e coloca o resultado no final de sons.
/// Faz isto mediante uma probabilidade. Se não tiver probabilidade suficiente copia os
/// intactos para os filhos.
bool Crossover::Reproduce(const std::vector< Chromossome > &parents
							, std::vector< Chromossome > &sons) const
{
	if (this->parents != parents.size())
	{
		return false;
	}

	if(Math::RandomPercentage() > this->probability)
	{
		for (int i = 0, j = 0; i < this->sons; i++, j++)
		{
			sons.push_back(parents[j]);
			
			if (j > (int)parents.size() - 1)
			{
                j = 0;
			}
		}

		return false;
	}
    Cross(parents, sons);

	return true;
}



/// Transforma os size vectores de vectores de genes em cromossomas que coloca no final de chromossomes.
void Crossover::GenesToChromossomes(const std::vector< double > *genes, const int size
										, std::vector< Chromossome > &chromossomes)
{
	for (int i = 0; i < size; i++)
	{
		chromossomes.push_back(Chromossome(genes[i]));
	}
}



/// Grava o crossover para o stream.
std::ostream& operator << (std::ostream& os, const Crossover& crossover)
{
	os << crossover.parents << std::endl;
	os << crossover.sons << std::endl;
	os << crossover.probability << std::endl;

	return crossover.Save(os);
}



/// Lê o crossover do stream.
std::istream& operator >> (std::istream& is, Crossover& crossover)
{
	is >> crossover.parents;
	is >> crossover.sons;
	is >> crossover.probability;

	return crossover.Load(is);
}



/// Grava o crossover para o stream.
std::ostream& Crossover::Save(std::ostream& os) const
{
	return os;
}



/// Lê o crossover do stream.
std::istream& Crossover::Load(std::istream& is)
{
	return is;
}



/// Lê o crossover apropriado do stream.
Crossover* Crossover::Read(std::istream& is)
{
	Crossover* crossover;
	int type;

	is >> type;

	switch((CrossoverType)type)
	{
		case Uniform:
			crossover = new UniformCrossover();
			break;

		case TwoPoint:
			crossover = new TwoPointCrossover();
			break;

		case UniformScanning:
			crossover = new UniformScanningCrossover();
			break;

		case NPoint:
			crossover = new NPointCrossover();
			break;

		case Diagonal:
			crossover = new DiagonalCrossover();
			break;

		default:
		case SinglePoint:
			crossover = new SinglePointCrossover();
			break;
	}
	is >> *crossover;

	return crossover;
}



/// Escreve o tipo de crossover.
std::string Crossover::ToString() const
{
	std::string aux;

	switch(Type())
	{
		case Uniform:
			aux = "Uniform";
			break;

		case TwoPoint:
			aux = "Two-Point";
			break;

		case UniformScanning:
			aux = "Uniform Scanning";
			break;

		case NPoint:
			aux = "Multi-point";
			break;

		case Diagonal:
			aux = "Diagonal";
			break;

		case SinglePoint:
			aux = "Single-Point";
			break;

		default:
			aux = "Nao reconhecido";
			break;
	}

	return String(this->GetProbability()).append(" ").append(aux);
}