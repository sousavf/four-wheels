#include <algorithm>
#include "StandardElitism.h"
#include "GeneticAlgorithm.h"

StandardElitism::StandardElitism()
{
	Init(0);
}



/// Cria um novo algoritmo de elitismo que escolhe elitistSize membros da popula��o.
StandardElitism::StandardElitism(int elitistSize)
{
	Init(elitistSize);
}



/// Cria um novo algoritmo de elitismo que escolhe elitistSize membros da popula��o.
void StandardElitism::Init(int elitistSize)
{
	SetElitistSize(elitistSize);
}



/// Destr�i a fun��o de elitismo
StandardElitism::~StandardElitism()
{
}



/// Escolhe da popula��o de ga os elitistSize melhores cromossomas.
std::vector< Chromossome > StandardElitism::Choose(const GeneticAlgorithm* ga) const
{
	std::vector< Chromossome > chromossomesOrdered, choosen;

	chromossomesOrdered = ga->GetChromossomes();
	sort(chromossomesOrdered.begin(), chromossomesOrdered.end(), Bigger);

	for (int i = 0; i < this->elitistSize; i++)
	{
		choosen.push_back(chromossomesOrdered[i]);
	}

	return choosen;
}



/// Define o tamanho da popula��o que escolhe (se value >= 0).
void StandardElitism::SetElitistSize(int value)
{
	if (value >= 0)
	{
		this->elitistSize = value;
	}
}



/// Devolve o tamanho da popula��o que escolhe.
int StandardElitism::GetElitistSize() const
{
	return this->elitistSize;
}



/// Indica se c1 � menor que c2.
bool StandardElitism::Bigger(Chromossome &c1, Chromossome &c2)
{
   return c1 > c2;
}



Elitism::ElitismType StandardElitism::Type() const
{
	return Standard;
}



std::ostream& StandardElitism::Save(std::ostream& os) const
{
	os << this->elitistSize;

	return os;
}



std::istream& StandardElitism::Load(std::istream& is)
{
	is >> this->elitistSize;

	return is;
}