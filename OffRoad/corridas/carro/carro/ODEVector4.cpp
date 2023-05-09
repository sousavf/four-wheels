#include "ODEHeaders.h"

using namespace ODE;

/// Cria um vector vazio
ODEVector4::ODEVector4()
{
	Init(0, 0, 0, 0);
}



/// Cria um vector com os valores a, b, c, d.
ODEVector4::ODEVector4(ODEReal a, ODEReal b, ODEReal c, ODEReal d)
{
	Init(a, b, c, d);
}



/// Cria o vector com informação igual a outro vector.
ODEVector4::ODEVector4(const ODEVector4 &v)
{
	ODEVector4 v2;
	
	v2 = v;
	Init(v2[0], v2[1], v2[2], v2[3]);
}



/// Inicia os dados do vector.
void ODEVector4::Init(ODEReal a, ODEReal b, ODEReal c, ODEReal d)
{
	this->data[0] = a;
	this->data[1] = b;
	this->data[2] = c;
	this->data[3] = d;
}



/// Destroi o vector.
ODEVector4::~ODEVector4()
{
}



/// Devolve o elemento na posição index.
ODEReal& ODEVector4::operator [] (int index)
{
	return this->data[index];
}



/// Iguala o vector a um vector de dReal.
ODEVector4& ODEVector4::operator = (const dReal* v)
{
	for (int i = 0; i < 4; i++)
	{
		this->data[i] = (ODEReal)v[i];
	}

	return *this;
}