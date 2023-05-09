#include <ode/ode.h>
#include <drawstuff/drawstuff.h>
#include "CylinderGeometry.h"

/// Cria um cilindro com raio e comprimento específicos.
CylinderGeometry::CylinderGeometry(const Space &space, double radius, double length)
{
	Init(space, radius, length, Geometry::DEFAULT_COLOR);
}



/// Cria um cilindro com raio, comprimento e cor específicas.
CylinderGeometry::CylinderGeometry(const Space &space, double radius, double length, Color color)
{
	Init(space, radius, length, color);
}



/// Define as características do cilindro e cria-o.
void CylinderGeometry::Init(const Space &space, double radius, double length, Color color)
{
	this->radius = radius;
	this->length = length;
	this->color = color;
	SetColor(color);
	this->geometry = dCreateCylinder(space.ID(), (dReal) radius, (dReal) length);
}



/// Destrói a instância.
CylinderGeometry::~CylinderGeometry()
{
}



/// Desenha o cilindro.
void CylinderGeometry::Draw()
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
	dsDrawCylinder(cpos, crot, (float) this->length, (float) this->radius);
}



/// Devolve a largura do cilindro.
double CylinderGeometry::Width()
{
	return this->radius;
}



/// Devolve a altura do cilindro.
double CylinderGeometry::Height()
{
	return this->radius;
}



/// Devolve o comprimento do cilindro.
double CylinderGeometry::Length()
{
	return this->length;
}