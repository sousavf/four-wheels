#include "ODEHeaders.h"
#include "Utilities.h"

using namespace ODE;

/// Cria um quaternion vazio.
ODEQuaternion::ODEQuaternion()
{
	Init(0, 0, 0, 0);
}



/// Cria um quaternion com os valores passados.
ODEQuaternion::ODEQuaternion(ODEReal w, ODEReal x, ODEReal y, ODEReal z)
{
	Init(w, x, y, z);
}



/// Cria um quaternion a partir de ouro.
ODEQuaternion::ODEQuaternion(const ODEQuaternion &q)
{
	ODEQuaternion q2;

	q2 = q;
	Init(q2[0], q2[1], q2[2], q2[3]);
}



/// Inicia o vector com os valores passados.
void ODEQuaternion::Init(ODEReal w, ODEReal x, ODEReal y, ODEReal z)
{
	this->data[0] = w;
	this->data[1] = x;
	this->data[2] = y;
	this->data[3] = z;
}



/// Destrói o vector.
ODEQuaternion::~ODEQuaternion()
{
}



/// Devolve o elemento na posição index do vector.
ODEReal& ODEQuaternion::operator [] (int index)
{
	return this->data[index];
}



/// Versão constante.
ODEReal ODEQuaternion::operator [] (int index) const
{
	return this->data[index];
}



/// Iguala um quaternion a um vector de dReal.
ODEQuaternion& ODEQuaternion::operator = (const dReal *q)
{
	this->data[0] = (ODEReal)q[0];
	this->data[1] = (ODEReal)q[1];
	this->data[2] = (ODEReal)q[2];
	this->data[3] = (ODEReal)q[3];

	return *this;
}



/// Define o quaternion a partir de um ângulo (em radianos) e das coordenadas que são afectadas.
/// E.g.: rodar 90º no eixo dos X:
///			(90º = PI / 2)
///			fromAxisAndAngle(1, 0, 0, PI/2);
void ODEQuaternion::fromAxisAndAngle(ODEReal ax, ODEReal ay, ODEReal az, ODEReal angle)
{
	dQuaternion q;

	dQFromAxisAndAngle(q, ax, ay, az, angle);
	*this = q;
}



/// Devolve os ângulos correspondente às coordenadas x, y, z (em graus).
const ODEVector3 ODEQuaternion::getEulerAngles() const
{
	float x, y, z, s, c, m00, m10, m20, m11, m21, m12, m22;
	int sign;

    m00 = 1.0f - 2.0f * (this->data[2] * this->data[2] + this->data[3] * this->data[3]);
    m10 = 2.0f * (this->data[1] * this->data[2] - this->data[0] * this->data[3]);
    m20 = 2.0f * (this->data[0] * this->data[2] + this->data[1] * this->data[3]);
    m11 = 1.0f - 2.0f * (this->data[1] * this->data[1] + this->data[3] * this->data[3]);
    m21 = 2.0f * (this->data[2] * this->data[3] - this->data[0] * this->data[1]);
    m12 = 2.0f * (this->data[0] * this->data[1] + this->data[2] * this->data[3]);
    m22 = 1.0f - 2.0f * (this->data[1] * this->data[1] + this->data[2] * this->data[2]);

    s = -m20;
    c = sqrt(m00 * m00 + m10 * m10);

	y = Utilities::ToDegrees(atan2(s, c));

    if (c > 0.001f)
	{
        x = Utilities::ToDegrees(atan2(m21, m22));
        z = Utilities::ToDegrees(atan2(m10, m00));
    }
	else
	{
        x = 0.0f;
		sign = (s > 0 ? 1 : (s < 0 ? -1 : 0));
        z = Utilities::ToDegrees(-sign * atan2(-m12, m11));
    }

	return ODEVector3(x, y, z);
}



/// Multiplica quaternion por vector.
ODEVector3 ODEQuaternion::operator* (const ODEVector3 &v) const
{
	ODEVector3 uv, uuv, q(this->data[1], this->data[2], this->data[3]);
	uv = q.crossProduct(v);
	uuv = q.crossProduct(uv);
	uv = uv * (2 * this->data[0]);
	uuv = uuv * 2;

	return v + uv + uuv;
}



/// Indica se os quaternions são iguais.
bool ODEQuaternion::operator == (const ODEQuaternion &q) const
{
	for (int i = 0; i < 4; i++)
	{
		if (this->data[i] != q[i])
		{
			return false;
		}
	}

	return true;
}



/// Iguala um quaternion a outro.
ODEQuaternion& ODEQuaternion::operator = (const ODEQuaternion &q)
{
	for (int i = 0; i < 4; i++)
	{
		this->data[i] = q[i];
	}

	return *this;
}