#include <ode/ode.h>
#include <drawstuff/drawstuff.h>
#include "SphereGeometry.h"

/// Cria uma esfera com um raio específico.
SphereGeometry::SphereGeometry(const Space &space, double radius)
{
	Init(space, radius, Geometry::DEFAULT_COLOR);
}



/// Cria uma esfera com raio e cor específicas.
SphereGeometry::SphereGeometry(const Space &space, double radius, Color color)
{
	Init(space, radius, color);
}



/// Define as características da esfera e cria-a.
void SphereGeometry::Init(const Space &space, double radius, Color color)
{
	this->radius = radius;
	this->color = color;
	SetColor(color);
	this->geometry = dCreateSphere(space.ID(), (dReal) radius);
}



/// Destrói a instância.
SphereGeometry::~SphereGeometry()
{
}



/// Desenha a esfera
void SphereGeometry::Draw()
{
	const dReal *CPos, *CRot;
	float color[3];

	GetColors(color);
	dsSetColorAlpha(color[0], color[1], color[2], Alpha());
	CPos = dGeomGetPosition(this->geometry);
	CRot = dGeomGetRotation(this->geometry);
	float cpos[3] = {CPos[0], CPos[1], CPos[2]};
	float crot[12] = {CRot[0], CRot[1], CRot[2], CRot[3], CRot[4],
						CRot[5], CRot[6], CRot[7], CRot[8],
						CRot[9], CRot[10], CRot[11]};
	dsDrawSphere(cpos, crot, (float) this->radius);
}



/// Devolve a largura da esfera.
double SphereGeometry::Width()
{
	return 2 * this->radius;
}



/// Devolve a altura da esfera.
double SphereGeometry::Height()
{
	return 2 * this->radius;
}



/// Devolve o comprimento da esfera.
double SphereGeometry::Length()
{
	return 2 * this->radius;
}