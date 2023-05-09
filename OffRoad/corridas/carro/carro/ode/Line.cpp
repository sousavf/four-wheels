#include "Line.h"
#include "Math.h"
#include <LIMITS.H>
#include <drawstuff/drawstuff.h>

/// Cria uma nova linha vazia (pontos 0, 0).
Line::Line()
{
	Init(Point(), Point());
}



/// Cria uma nova linha a partir de outra.
Line::Line(Line &anotherLine)
{
	Init(anotherLine.GetP1(), anotherLine.GetP2());
}



/// Cria uma nova linha através de 2 pontos.
Line::Line(double x1, double y1, double x2, double y2)
{
	Init(Point(x1, y1), Point(x2, y2));
}



/// Cria uma nova linha através de 2 pontos.
Line::Line(Point p1, Point p2)
{
	Init(p1, p2);
}



/// Cria uma nova linha através de 2 pontos.
void Line::Init(Point p1, Point p2)
{
	this->p1 = p1;
	this->p2 = p2;
	SetMB();
}



/// Destrói a linha.
Line::~Line()
{
}



/// Define o valor de p1.
void Line::SetP1(Point p1)
{
	this->p1 = p1;
	SetMB();
}



/// Define o valor de p2.
void Line::SetP2(Point p2)
{
	this->p2 = p2;
	SetMB();
}



/// Devolve o valor de p1.
Line::Point Line::GetP1()
{
	return this->p1;
}



/// Devolve o valor de p2.
Line::Point Line::GetP2()
{
	return this->p2;
}



/// Devolve o valor de m.
double Line::GetM()
{
	return this->m;
}



/// Devolve o valor de b.
double Line::GetB()
{
	return this->b;
}



/// Corrige o valor de m e b tendo em conta os 2 pontos que constituem al inha.
void Line::SetMB()
{
	if (this->p1.GetX() != this->p2.GetX())
	{
		this->m = (this->p2.GetY() - this->p1.GetY()) / (this->p2.GetX() - this->p1.GetX());
	}
	else
	{
		this->m = INT_MAX / 2;
	}
	this->b = this->p1.GetY() - this->m * this->p1.GetX();
}



/// Indica se a linha intersecta point.
bool Line::Intersects(Point point)
{
	double y_;

	if ( (point.GetX() >= Math::Min(this->p1.GetX(), this->p2.GetX()))
			&& (point.GetX() <= Math::Max(this->p1.GetX(), this->p2.GetX()))
			&& (point.GetY() >= Math::Min(this->p1.GetY(), this->p2.GetY()))
			&& (point.GetY() <= Math::Max(this->p1.GetY(), this->p2.GetY())) )
	{
		y_ = this->m * point.GetX() + this->b;

		return (Math::Round(y_, 5) == Math::Round(point.GetY(), 5));
	}

	return false;
}



/// Indica se esta linha intersecta anotherLine.
bool Line::Intersects(Line &anotherLine)
{
	if (this->m != anotherLine.m)
	{
		Point p;
		p.SetX(-(this->b - anotherLine.b) / (this->m - anotherLine.m));
		p.SetY(this->m * p.GetX() + this->b);

		if ( this->Intersects(p) && anotherLine.Intersects(p) )
		{
			return true;
		}
	}

	return false;
}



/// Desenha uma linha mediante as coordenadas de 2 pontos e uma cor específica.
void Line::Draw(XYZ p1, XYZ p2, Geometry::Color color)
{
	float pos1[3], pos2[3], rgb[3];

	pos1[0] = (float)p1.x;
	pos1[1] = (float)p1.y;
	pos1[2] = (float)p1.z;
	pos2[0] = (float)p2.x;
	pos2[1] = (float)p2.y;
	pos2[2] = (float)p2.z;
	Geometry::GetColors(rgb, color);
	dsSetColor(rgb[0], rgb[1], rgb[2]);
	dsDrawLine(pos1, pos2);
}