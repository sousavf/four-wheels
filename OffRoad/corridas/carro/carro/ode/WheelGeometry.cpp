#include <ode/ode.h>
#include <drawstuff/drawstuff.h>
#include "WheelGeometry.h"

/// Cria uma geomtetria de uma roda em space com radius e width.
WheelGeometry::WheelGeometry(const Space &space, double radius, double width):SphereGeometry(space, radius)
{
	Init(space, radius, width, Geometry::DEFAULT_COLOR);
}



/// Cria uma geomtetria de uma roda em space com radius, width e color.
WheelGeometry::WheelGeometry(const Space &space, double radius, double width, Color color):SphereGeometry(space, radius, color)
{
	Init(space, radius, width, color);
}



/// Cria uma geomtetria de uma roda em space com radius, width e color.
void WheelGeometry::Init(const Space &space, double radius, double width, Color color)
{
	this->radius = radius;
	this->width = width;
}



/// Destrói a geometria.
WheelGeometry::~WheelGeometry()
{
}



/// Desenha a geometria da roda.
void WheelGeometry::Draw()
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
	dsDrawCylinder(cpos, crot, (float) this->width, (float) this->radius);
}


