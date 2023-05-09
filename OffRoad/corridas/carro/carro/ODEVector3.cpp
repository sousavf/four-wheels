#include "ODEHeaders.h"

using namespace ODE;

/// Cria um vector vazio
ODEVector3::ODEVector3()
{
	Init(0, 0, 0);
}



/// Cria um vector com os valores x, y, z.
ODEVector3::ODEVector3(ODEReal x, ODEReal y, ODEReal z)
{
	Init(x, y, z);
}



/// Cria o vector com informação igual a outro vector.
ODEVector3::ODEVector3(const ODEVector3 &v)
{
	Init(v[0], v[1], v[2]);
}



/// Inicia os dados do vector.
void ODEVector3::Init(ODEReal x, ODEReal y, ODEReal z)
{
	this->data[0] = x;
	this->data[1] = y;
	this->data[2] = z;
}



/// Destroi o vector.
ODEVector3::~ODEVector3()
{
}



/// Pode ser usado para calcular o ângulo entre 2 vectores. Se ambos são vectores unitários,
/// representa o cosseno do ângulo, senão tem de ser dividido pelo produto do comprimento
/// de ambos os vectores para se obter o cosseno.
ODEReal ODEVector3::dotProduct(const ODEVector3& v) const
{
	return this->data[0] * v[0] + this->data[1] * v[1] + this->data[2] * v[2];
}



/// Calcula o vector perpendicular aos dois vectores.
ODEVector3 ODEVector3::crossProduct(const ODEVector3 &v) const
{
	return ODEVector3(this->data[1] * v[2] - this->data[2] * v[1],
				this->data[2] * v[0] - this->data[0] * v[2],
				this->data[0] * v[1] - this->data[1] * v[0]);
}



/// sqrt(x^2 + y^2 + z^2)
ODEReal ODEVector3::length() const
{
	return sqrt(this->data[0] * this->data[0]
			+ this->data[1] * this->data[1]
			+ this->data[2] * this->data[2]);
}



/// Devolve o elemento na posição index.
ODEReal& ODEVector3::operator [] (int index)
{
	return this->data[index];
}



/// Versão constante para quando não é necessário alterar e vector é constante.
ODEReal ODEVector3::operator [] (int index) const
{
	return this->data[index];
}



/// Iguala o vector a um vector de dReal.
ODEVector3& ODEVector3::operator = (const dReal* v)
{
	this->data[0] = (ODEReal)v[0];
	this->data[1] = (ODEReal)v[1];
	this->data[2] = (ODEReal)v[2];

	return *this;
}



/// Multiplica um vector por outro.
ODEVector3 ODEVector3::operator * (const ODEVector3& v) const
{
	return ODEVector3(this->data[0] * v[0], this->data[1] * v[1], this->data[2] * v[2]);
}



/// Subtrai um vector com outro.
ODEVector3 ODEVector3::operator - (const ODEVector3& v) const
{
	return ODEVector3(this->data[0] - v[0], this->data[1] - v[1], this->data[2] - v[2]);
}



/// Soma um vector com outro.
ODEVector3 ODEVector3::operator + (const ODEVector3& v) const
{
	return ODEVector3(this->data[0] + v[0], this->data[1] + v[1], this->data[2] + v[2]);
}



/// Divide um vector por outro.
ODEVector3 ODEVector3::operator / (const ODEVector3& v) const
{
	return ODEVector3(this->data[0] / v[0], this->data[1] / v[1], this->data[2] / v[2]);
}



/// Devolve um vector igual.
ODEVector3 ODEVector3::operator + () const
{
	return ODEVector3(*this);
}



/// Devolve um vector negativo a este.
ODEVector3 ODEVector3::operator - () const
{
	return ODEVector3(-this->data[0], -this->data[1], -this->data[2]);
}



/// Multiplica o vector por uma constante.
ODEVector3 ODEVector3::operator * (ODEReal r) const
{
	return ODEVector3(this->data[0] * r, this->data[1] * r, this->data[2] * r);
}



/// Divide o vector por constante.
ODEVector3 ODEVector3::operator / (ODEReal r) const
{
	return ODEVector3(this->data[0] / r, this->data[1] / r, this->data[2] / r);
}



/// Multiplica constante por vector.
ODEVector3 operator * (ODEReal r, const ODEVector3& v)
{
	return ODEVector3(r * v[0], v[1] * r, v[2] * r);
}



/// Divide constante por vector.
ODEVector3 operator / (ODEReal r, const ODEVector3& v)
{
	return ODEVector3(r / v[0], r / v[1], r / v[2]);
}



/// Soma constante com vector.
ODEVector3 operator + (ODEReal r, const ODEVector3& v)
{
	return ODEVector3(v[0] + r, v[1] + r, v[2] + r);
}



/// Subtrai vector a constante.
ODEVector3 operator - (ODEReal r, const ODEVector3& v)
{
	return ODEVector3(r - v[0], r - v[1], r - v[2]);
}



/// Soma vector a constante.
ODEVector3 operator + (const ODEVector3& v, ODEReal r)
{
	return ODEVector3(v[0] + r, v[1] + r, v[2] + r);
}



/// Subtrai constante a vector.
ODEVector3 operator - (const ODEVector3& v, ODEReal r)
{
	return ODEVector3(v[0] - r, v[1] - r, v[2] - r);
}



/// Indica se os dois vectores são iguais.
bool ODEVector3::operator == (const ODEVector3& v) const
{
	for (int i = 0; i < 3; i++)
	{
		if (this->data[i] != v[1])
		{
			return false;
		}
	}

	return true;
}



/// Iguala um vector a outro.
ODEVector3& ODEVector3::operator = (const ODEVector3& v)
{
	for (int i = 0; i < 3; i++)
	{
		this->data[i] = v[i];
	}

	return *this;
}