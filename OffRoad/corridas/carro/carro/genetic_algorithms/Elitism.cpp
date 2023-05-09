#include "Elitism.h"
#include "StandardElitism.h"

std::ostream& operator << (std::ostream& os, const Elitism& elitism)
{
	return elitism.Save(os);
}



std::istream& operator >> (std::istream& is, Elitism& elitism)
{
	return elitism.Load(is);
}



/// Lê o elitismo apropriado do stream.
Elitism* Elitism::Read(std::istream& is)
{
	Elitism* elitism;
	int type;

	is >> type;

	switch((ElitismType)type)
	{
		default:
		case Standard:
			elitism = new StandardElitism();
			is >> *elitism;
			break;
	}

	return elitism;
}



/// Escreve o nome do elitismo.
std::string Elitism::ToString() const
{
	std::string aux;

	switch(Type())
	{
		case Standard:
			aux = "Standard";
			break;

		default:
			aux = "Nao reconhecido";
			break;
	}

	return aux;
}