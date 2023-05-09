#include "ODEHeaders.h"

using namespace ODE;

/// Cria um vector vazio.
ODEVector2::ODEVector2()
{
	Init(0, 0);
}



/// Cria o vector a partir de 2 coordenadas.
ODEVector2::ODEVector2(ODEReal x, ODEReal y)
{
	Init(x, y);
}



/// Cria o vector a partir de outro.
ODEVector2::ODEVector2(const ODEVector2 &v)
{
	Init(v[0], v[1]);
}



/// Define os valores do vector.
void ODEVector2::Init(ODEReal x, ODEReal y)
{
	this->data[0] = x;
	this->data[1] = y;
}



/// Destrói o vector.
ODEVector2::~ODEVector2()
{
}



/// Iguala o vector a outro.
ODEVector2& ODEVector2::operator = (const ODEVector2 &v)
{
	this->data[0] = v[0];
	this->data[1] = v[1];

	return *this;
}



/// Devolve o elemento correspondente a index.
ODEReal& ODEVector2::operator [] (int index)
{
	return this->data[index];
}



/// Versão constante do operador anterior.
ODEReal ODEVector2::operator [] (int index) const
{
	return this->data[index];
}