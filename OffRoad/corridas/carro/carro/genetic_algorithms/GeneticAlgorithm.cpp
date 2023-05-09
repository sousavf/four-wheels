#include <vector>
#include "../ode/Math.h"
#include "GeneticAlgorithm.h"

/// Defini��o das vari�veis est�ticas.
const double GeneticAlgorithm::MUTATION_RATE = 0.15;
const double GeneticAlgorithm::CROSSOVER_RATE = 0.7;
const double GeneticAlgorithm::MAX_PERTURBATION = 0.3;

void GeneticAlgorithm::RemoveChromossome(int i)
{
	this->chromossomes.erase(this->chromossomes.begin() + i);
}



/// Cria um algoritmo a partir de um conjunto de cromossomas.
GeneticAlgorithm::GeneticAlgorithm(std::vector< Chromossome > &chromossomes)
{
	Init(MUTATION_RATE, CROSSOVER_RATE, chromossomes);
}



/// Cria um algoritmo a partir de um conjunto de cromossomas com valores espec�ficos
/// para a percentagem de muta��es/crossovers.
GeneticAlgorithm::GeneticAlgorithm(double mutationRate, double crossoverRate
									, std::vector< Chromossome > &chromossomes)
{
	Init(mutationRate, crossoverRate, chromossomes);
}



/// Cria um algoritmo para uma popula��o de tamanho population_size com genes genes.
GeneticAlgorithm::GeneticAlgorithm(int population_size, int genes)
{
	for(int i = 0; i < population_size; i++)
	{
		this->chromossomes.push_back(Chromossome(genes));
	}
	Init(MUTATION_RATE, CROSSOVER_RATE, this->chromossomes);
}



/// Cria um algoritmo com valores espec�ficos para a percentagem de muta��es/crossovers, tamanho da popula��o e de cada genes.
GeneticAlgorithm::GeneticAlgorithm(double mutationRate, double crossoverRate, int population_size, int genes)
{
	for(int i = 0; i < population_size; i++)
	{
		this->chromossomes.push_back(Chromossome(genes));
	}
	Init(mutationRate, crossoverRate, this->chromossomes);
}



/// Destr�i o algoritmo.
GeneticAlgorithm::~GeneticAlgorithm()
{
}



/// Inicia as vari�veis do algoritmo.
void GeneticAlgorithm::Init(double mutationRate, double crossoverRate, std::vector< Chromossome > &chromossomes)
{
	this->mutationRate = mutationRate;
	this->chromossomes = chromossomes;
	this->maxPerturbation = MAX_PERTURBATION;
	this->totalFitness = 0;
	this->generationCount = 0;
	this->selection = NULL;//new RoulletteWheelSelection();
	this->crossover = NULL;//new SinglePointCrossover(crossoverRate);
	this->elitism = NULL;
	this->doElitism = false;
	this->scaleAndInvert = false;
}



/// Faz a muta��o de um cromossoma tendo em conta mutation rate.
void GeneticAlgorithm::Mutate(Chromossome &chromossome)
{
	for(int i = 0; i < chromossome.Length(); i++)
	{
		if(Math::RandomPercentage() < this->mutationRate)
		{
			chromossome[i] += Math::RandomDouble() * this->maxPerturbation;
		}
	}
}



/// Escolhe um cromossoma da lista de cromossomas usando o m�todo de selec��o definido.
Chromossome& GeneticAlgorithm::Select()
{
	return this->selection->Select(this);
}



/// Estabelece a perturba��o m�xima com que um gene sofre uma muta��o.
void GeneticAlgorithm::SetMaxPerturbation(double maxPerturbation)
{
	this->maxPerturbation = maxPerturbation;
}



/// Devolve o somat�rio da fitness de todos os cromossomas.
double GeneticAlgorithm::UpdateTotalFitness()
{
	double total = 0;

	for(unsigned int i = 0; i < this->chromossomes.size(); i++)
	{
		total += this->chromossomes[i].fitness;
	}
	this->totalFitness = Math::Max(total, INT_MIN);
	this->totalFitness = Math::Min(this->totalFitness, INT_MAX);

    return total;
}



/// Avan�a os cromossomas em uma gera��o.
void GeneticAlgorithm::Epoch()
{
	std::vector< Chromossome > new_generation, parents, sons;

	if (this->scaleAndInvert)
	{
		ScaleAndInvertFitness();
	}
	UpdateTotalFitness();

	if ( this->doElitism && (this->elitism != NULL) )
	{
		new_generation = this->elitism->Choose(this);
	}

	while (new_generation.size() < this->chromossomes.size())
	{
		parents.clear();
		sons.clear();

		while ((int)parents.size() < this->crossover->GetParentsCount())
		{
			parents.push_back(Select());
		}
		this->crossover->Reproduce(parents, sons);

		for (int i = 0; i < (int)sons.size(); i++)
		{
			Mutate(sons[i]);
			new_generation.push_back(sons[i]);
		}
	}
	
	// pode ter ficado com uma popula��o maior por causa do crossover
	while (new_generation.size() > this->chromossomes.size())
	{
		new_generation.erase(new_generation.end() - 1);
	}

	// apagar gera��o actual
	while ((int)this->chromossomes.size())
	{
		this->chromossomes[0].~Chromossome();
		this->chromossomes.erase(this->chromossomes.begin());
	}
	this->chromossomes = new_generation;
	this->generationCount++;
}



/// Devolve os genes de todos os cromossomas.
std::vector< double > GeneticAlgorithm::GetGenes()
{
	std::vector< double > genes;

	for(unsigned int i = 0; i < this->chromossomes.size(); i++)
	{
		this->chromossomes[i].GetGenes(genes);
	}

	return genes;
}


/// Devolve o cromossoma na posi��o respectiva.
Chromossome& GeneticAlgorithm::operator[] (const int &index)
{
	return this->chromossomes[index];
}



/// Estabelece a probabilidade de efectuar uma muta��o.
void GeneticAlgorithm::SetMutationRate(double mutationRate)
{
	this->mutationRate = mutationRate;
}



/// Devolve o n�mero de gera��es que o algoritmo j� correu.
int GeneticAlgorithm::GetGenerationCount() const
{
	return this->generationCount;
}



/// Adiciona um cromossoma.
void GeneticAlgorithm::AddChromossome(Chromossome &chromossome)
{
	this->chromossomes.push_back(chromossome);
}




void GeneticAlgorithm::Replace(Chromossome* chromossomes, int size)
{
	std::vector< Chromossome > newPopulation;

	for (int i = 0; i < size; i++)
	{
		newPopulation.push_back(chromossomes[i]);
	}
	Replace(newPopulation);
}




/// Substitui os cromossomas do algoritmo pelos cromossomas em chromossomes.
void GeneticAlgorithm::Replace(std::vector< Chromossome > &chromossomes)
{
	this->totalFitness = 0;
	//this->generationCount = 0;
	
	// apagar gera��o actual
	while ((int)this->chromossomes.size())
	{
		this->chromossomes[0].~Chromossome();
		this->chromossomes.erase(this->chromossomes.begin());
	}
	this->chromossomes = chromossomes;
}



/// Devolve o tamanho da popula��o.
int GeneticAlgorithm::PopulationSize() const
{
	return (int)this->chromossomes.size();
}



/// Devolve a fitness total da popula��o.
double GeneticAlgorithm::TotalFitness() const
{
	return this->totalFitness;
}



/// Define a fun��o de selec��o que o algoritmo vai usar.
void GeneticAlgorithm::SetSelection(Selection* selection)
{
	this->selection = selection;
}



/// Devolve todos os cromossomas do algoritmo gen�tico.
std::vector< Chromossome > GeneticAlgorithm::GetChromossomes() const
{
	return this->chromossomes;
}



/// Define a fun��o de elitismo que � usada.
void GeneticAlgorithm::SetElitism(Elitism* function)
{
	this->elitism = function;
}



/// Devolve a fun��o de elitism usada.
Elitism* GeneticAlgorithm::GetElitism() const
{
	return this->elitism;
}



/// Define se fazemos elitism aquando de uma nova gera��o ou n�o.
void GeneticAlgorithm::SetDoElitism(bool value)
{
	this->doElitism = value;
}



/// Indica se fazemos elitism ou n�o.
bool GeneticAlgorithm::GetDoElitism() const
{
	return this->doElitism;
}



/// Define a fun��o de crossover.
void GeneticAlgorithm::SetCrossover(Crossover* crossover)
{
	this->crossover = crossover;
}



/// Devolve a fun��o de crossover.
Crossover* GeneticAlgorithm::GetCrossover() const
{
	return this->crossover;
}



/// Estabelece a gera��o em que vai. value tem de ser >= 0.
void GeneticAlgorithm::SetGenerationCount(int value)
{
	if (value >= 0)
	{
		this->generationCount = value;
	}
}



/// Devolve a probabilidade de muta��o.
double GeneticAlgorithm::GetMutationRate() const
{
	return this->mutationRate;
}



/// Devolve o valor da perturba��o m�xima.
double GeneticAlgorithm::GetMaxPerturbation() const
{
	return this->maxPerturbation;
}



/// Devolve a selec��o.
Selection* GeneticAlgorithm::GetSelection() const
{
	return this->selection;
}



/// As fitness com menor valor passam a ser as de maior valor e depois sao todas
/// escalonadas de forma que a nova fitness com menor valor fica com uma fitness de 0.
/// Esta fun��o d� jeito quando � mais f�cil estabelecer uma fitness de menor valor,
/// mas queremos valorizar o oposto (e.g.: queremos que o melhor cromossoma seja aquele
/// que tenha a menor dist�ncia - � mais f�cil calcular a fitness como sendo a dist�ncia
/// e depois escalonar todas as fitness de forma que o melhor cromossoma, o que est� mais perto
/// ou com menor dist�ncia, fica com uma fitness maior).
/// E.g.:
///		Fitness antiga
///		100, 20, 80, 5	-> descobrir maior fitness: 100
///						-> nova fitness: 100 - fitness antiga
///		Nova fitness
///		0, 80, 20, 95
void GeneticAlgorithm::ScaleAndInvertFitness()
{
	double max;

	for (int i = 0; i < (int)this->chromossomes.size(); i++)
	{
		if ( (i == 0) || (this->chromossomes[i].GetFitness() > max) )
		{
			max = this->chromossomes[i].GetFitness();
		}
	}

	for (int i = 0; i < (int)this->chromossomes.size(); i++)
	{
		this->chromossomes[i].SetFitness(max - this->chromossomes[i].GetFitness());
	}
}



/// Indica se executa o m�todo ScaleAndInvertFitness() antes de efectuar uma nova gera��o.
bool GeneticAlgorithm::GetScaleAndInvertFitness() const
{
	return this->scaleAndInvert;
}



/// Estabelece se executa o m�todo ScaleAndInvertFitness() antes de efectuar uma nova gera��o.
void GeneticAlgorithm::SetScaleAndInvertFitness(bool value)
{
	this->scaleAndInvert = value;
}



/// Indica se o m�todo ScaleAndInvertFitness() est� a funcionar correctamente.
bool GeneticAlgorithm::ScaleAndInvertCheck()
{
	GeneticAlgorithm ga = GeneticAlgorithm(3, 1);

	ga[0].SetFitness(100);
	ga[1].SetFitness(20);
	ga[2].SetFitness(50);
	ga.ScaleAndInvertFitness();

	if ( (ga[0].GetFitness() == 0) && (ga[1].GetFitness() == 80) && (ga[2].GetFitness() == 50) )
	{
		return true;
	}

	return false;
}