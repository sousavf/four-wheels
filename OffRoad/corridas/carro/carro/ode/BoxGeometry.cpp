#include <ode/ode.h>
#include <drawstuff/drawstuff.h>
#include "BoxGeometry.h"

/// Não faz nada.
BoxGeometry::BoxGeometry()
{
}



/// Cria uma caixa com largura, comprimento e altura igual a size e com a cor default.
BoxGeometry::BoxGeometry(const Space &space, double size)
{
	Init(space, size, size, size, Geometry::DEFAULT_COLOR);
}



/// Cria uma caixa com largura, comprimento e altura igual a size e com a cor color.
BoxGeometry::BoxGeometry(const Space &space, double size, Color color)
{
	Init(space, size, size, size, color);
}



/// Cria uma caixa com determinadas medidas e com cor default.
BoxGeometry::BoxGeometry(const Space &space, double width, double height, double length)
{
	Init(space, width, height, length, Geometry::DEFAULT_COLOR);
}



/// Cria uma caixa com determinadas medidas e cor.
BoxGeometry::BoxGeometry(const Space &space, double width, double height, double length, Color color)
{
	Init(space, width, height, length, color);
}



/// Define as características da caixa e cria-a.
void BoxGeometry::Init(const Space &space, double width, double height, double length, Color color)
{
	this->width = width;
	this->height = height;
	this->length = length;
	SetColor(color);
	this->geometry = dCreateBox(space.ID(), (dReal) width, (dReal) length, (dReal) height);
}



/// Destrói a instância.
BoxGeometry::~BoxGeometry()
{
}



/// Desenha a caixa
void BoxGeometry::Draw()
{
	dVector3 ss;
	float color[3];

	GetColors(color);
	dsSetColorAlpha(color[0], color[1], color[2], Alpha());
	dGeomBoxGetLengths(this->geometry, ss);
    dsDrawBox(dGeomGetPosition(this->geometry), dGeomGetRotation(this->geometry), ss);
}



/// Devolve a largura da caixa.
double BoxGeometry::Width()
{
	return this->width;
}



/// Devolve a altura da caixa.
double BoxGeometry::Height()
{
	return this->height;
}



/// Devolve o comprimento da caixa.
double BoxGeometry::Length()
{
	return this->length;
}