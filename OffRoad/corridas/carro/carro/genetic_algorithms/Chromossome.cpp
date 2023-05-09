#include "Chromossome.h"
#include "../ode/Math.h"
#include "../ode/Auxiliary.h"

/// Cria um novo chromossoma vazio.
Chromossome::Chromossome()
{
	this->fitness = 0;
}



/// Cria um novo chromossoma com genes com valores à sorte de -1 a 1.
Chromossome::Chromossome(int genes)
{
	for(int i = 0; i < genes; i++)
	{
		this->genes.push_back(Math::RandomDouble());
	}
	this->fitness = 0;
}



/// Cria um novo chromossome a partir de outro.
Chromossome::Chromossome(const Chromossome &another_chromo)
{
	this->genes = another_chromo.genes;
	SetFitness(another_chromo.fitness);
	int s = (int)this->genes.size();
}



/// Cria uma novo cromossoma a partir de um grupo de genes.
Chromossome::Chromossome(const std::vector< double > &genes)
{
	this->genes = genes;
	this->fitness = 0;
}



/// Cria um novo cromossoma a partir de um grupo de genes e com determinada fitness.
Chromossome::Chromossome(const std::vector< double > &genes, double fitness)
{
	this->genes = genes;
	this->fitness = fitness;
}



/// Destrói o cromossoma.
Chromossome::~Chromossome()
{
}



/// Devolve true se a fitness deste cromossoma for menor que a fitness de another_chromo.
bool Chromossome::operator < (const Chromossome &another_chromo)
{
	return (this->fitness < another_chromo.fitness);
}



/// Devolve true se a fitness deste cromossoma for maior que a fitness de another_chromo.
bool Chromossome::operator > (const Chromossome &another_chromo)
{
	return (this->fitness > another_chromo.fitness);
}



/// Devolve a fitness do respectivo cromossoma.
double Chromossome::GetFitness()
{
	return this->fitness;
}



/// Devolve o gene na posição respectiva.
double& Chromossome::operator[] (const int &index)
{
	return this->genes[index];
}



/// Devolve o número de genes que o cromossoma tem.
int Chromossome::Length() const
{
	return (int) this->genes.size();
}



/// Coloca os genes deste cromossoma no final do vector genes
void Chromossome::GetGenes(std::vector< double > &genes)
{
	for(unsigned int i = 0; i < this->genes.size(); i++)
	{
		genes.push_back(this->genes[i]);
	}
}



/// Estabelece a fitness do cromossoma. Se a fitness ficar inferior a 0, põe fitness igual a zero.
void Chromossome::SetFitness(double fitness)
{
	this->fitness = fitness;
}



/// Aumenta a fitness do cromossoma pela quantia indicada.
void Chromossome::IncFitness(double fitness)
{
	this->fitness += fitness;
}



/// Decrementa a fitness do cromossoma pela quantia indicada. Se a fitness ficar inferior a 0, põe fitness igual a zero.
void Chromossome::DecFitness(double fitness)
{
	this->fitness -= fitness;
}



/// Devolve o valor dos genes do cromossoma.
std::vector< double > Chromossome::GetGenes() const
{
	return this->genes;
}



/// Substitui os genes do cromossoma pela informação contida no vector genes.
void Chromossome::SetGenes(std::vector< double > &genes)
{
	this->genes = genes;
}



/// Devolve true se dois cromossomas forem iguais e false em contrário
bool Chromossome::operator == (const Chromossome &another_chromo)
{
	if (this->genes.size() != another_chromo.genes.size())
	{
		return false;
	}

	for (int i = 0; i < (int)this->genes.size(); i++)
	{
		if (this->genes[i] != another_chromo.genes[i])
		{
			return false;
		}
	}

	return true;
}



/// Grava o cromossoma para o stream.
std::ostream& operator << (std::ostream& os, const Chromossome& chromossome)
{
	os << ToString(chromossome.fitness) << std::endl;
	os << (int)chromossome.genes.size() << std::endl;

	for (int i = 0; i < (int)chromossome.genes.size(); i++)
	{
		os << ToString(chromossome.genes[i]) << " ";
	}
	os << std::endl;

	return os;
}



/// Lê o cromossoma do stream.
std::istream& operator >> (std::istream& is, Chromossome& chromossome)
{
	int size;
	double gene;

	is >> chromossome.fitness;
	is >> size;
	chromossome.genes.clear();

	for (int i = 0; i < size; i++)
	{
		is >> gene;
		chromossome.genes.push_back(gene);
	}

	return is;
}