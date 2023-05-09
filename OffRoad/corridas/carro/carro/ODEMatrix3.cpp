#include "ODEHeaders.h"

using namespace ODE;

/// Cria uma matriz vazia.
ODEMatrix3::ODEMatrix3()
{
	ODEReal m[12];

	for (int i = 0; i < 12; i++)
	{
		m[i] = 0;
	}
	Init(m);
}



/// Cria uma matriz a partir de um vector de ODEReals.
ODEMatrix3::ODEMatrix3(const ODEReal* m)
{
	Init(m);
}



/// Cria a matriz com informa��o igual a outra matriz.
ODEMatrix3::ODEMatrix3(const ODEMatrix3 &m)
{
	for (int i = 0; i < 12; i++)
	{
		this->data[i] = m.data[i];
	}
}



/// Inicia os dados da matriz.
void ODEMatrix3::Init(const ODEReal* m)
{
	for (int i = 0; i < 12; i++)
	{
		this->data[i] = m[i];
	}
}



/// Destroi a matriz.
ODEMatrix3::~ODEMatrix3()
{
}



/// Define a matriz a partir de um �ngulo (em radianos) e das coordenadas que s�o afectadas.
/// E.g.: rodar 90� no eixo dos X:
///			(90� = PI / 2)
///			fromAxisAndAngle(1, 0, 0, PI/2);
void ODEMatrix3::fromAxisAndAngle(ODEReal ax, ODEReal ay, ODEReal az, ODEReal angle)
{
	dMatrix3 m;
	
	dRFromAxisAndAngle(m, ax, ay, az, angle);
	*this = m;
}



/// Devolve o elemento na posi��o index.
ODEReal& ODEMatrix3::operator [] (int index)
{
	return this->data[index];
}



/// Vers�� constante.
ODEReal ODEMatrix3::operator [] (int index) const
{
	return this->data[index];
}



/// Iguala a matriz a um vector de dReal.
ODEMatrix3& ODEMatrix3::operator = (const dReal* m)
{
	for (int i = 0; i < 12; i++)
	{
		this->data[i] = (ODEReal)m[i];
	}

	return *this;
}