#include "ODEHeaders.h"

using namespace ODE;

/// Devolve a definição correspondente a b.
ODETrackSegmentDefinition ODETrackSegmentDefinition::get(Block b)
{
	ODEVector3 size = ODEVector3(15, 15, 15);
	ODEReal border = 0.01f;
	ODEReal sidelinesWidth = 15 * 0.156f;
	ODEReal rampHeight = 1.0f;

	switch (b)
	{
	/// | / \ |
	/// |  |  |
	/// |  |  |
	case StartStraightFront:
		return ODETrackSegmentDefinition(Right, Left, ODETrackSegmentDefinition::StartStraightFront, true, Front, size, border, sidelinesWidth, 0);

	/// |  |  |
	/// |  |  |
	/// | \ / |
	case StartStraightBack:
		return ODETrackSegmentDefinition(Right, Left, ODETrackSegmentDefinition::StartStraightBack, true, Back, size, border, sidelinesWidth, 0);

	/// ____
	///
	/// <---
	/// ____
	case StartStraightLeft:
		return ODETrackSegmentDefinition(Front, Back, ODETrackSegmentDefinition::StartStraightLeft, true, Left, size, border, sidelinesWidth, 0);

	/// ____
	///
	/// --->
	/// ____
	case StartStraightRight:
		return ODETrackSegmentDefinition(Front, Back, ODETrackSegmentDefinition::StartStraightRight, true, Right, size, border, sidelinesWidth, 0);

	/// | |
	/// | |
	case Straight:
		return ODETrackSegmentDefinition(Right, Left, ODETrackSegmentDefinition::Straight, false, Front, size, border, sidelinesWidth, 0);

	/// ____
	/// ____
	case StraightSide:
		return ODETrackSegmentDefinition(Front, Back, ODETrackSegmentDefinition::StraightSide, false, Front, size, border, sidelinesWidth, 0);
		
	///  ____
	/// |
	/// |
	case Curve90BottomToRight:
		return ODETrackSegmentDefinition(Front, Left, ODETrackSegmentDefinition::Curve90BottomToRight, false, Front, size, border, sidelinesWidth, 0);

	/// ____
	///     |
	///     |
	case Curve90LeftToBottom:
		return ODETrackSegmentDefinition(Front, Right, ODETrackSegmentDefinition::Curve90LeftToBottom, false, Front, size, border, sidelinesWidth, 0);
		
	/// |
	/// |____
	case Curve90TopToRight:
		return ODETrackSegmentDefinition(Back, Left, ODETrackSegmentDefinition::Curve90TopToRight, false, Front, size, border, sidelinesWidth, 0);

	///     |
	/// ____|
	case Curve90LeftToTop:
		return ODETrackSegmentDefinition(Right, Back, ODETrackSegmentDefinition::Curve90LeftToTop, false, Front, size, border, sidelinesWidth, 0);

	/// |  /|
	/// |/  |
	/// |\  |
	/// |  \|
	case RampStraightElevated:
		return ODETrackSegmentDefinition(Right, Left, ODETrackSegmentDefinition::RampStraightElevated, false, Front, size, border, sidelinesWidth, rampHeight);

	/// |\  |
	/// |  \|
	/// |  /|
	/// |/  |
	case RampStraightSunken:
		return ODETrackSegmentDefinition(Right, Left, ODETrackSegmentDefinition::RampStraightSunken, false, Front, size, border, sidelinesWidth, -rampHeight);

	///    ,/ \,
	/// __/     \__
	///    ,/ \,
	/// __/     \__
	case RampStraightSideElevated:
		return ODETrackSegmentDefinition(Front, Back, ODETrackSegmentDefinition::RampStraightSideElevated, false, Front, size, border, sidelinesWidth, rampHeight);

	/// __       __
	///	  \,   ,/
	/// __  \ /  __
	///   \,   ,/
	///     \ /
	case RampStraightSideSunken:
		return ODETrackSegmentDefinition(Front, Back, ODETrackSegmentDefinition::RampStraightSideSunken, false, Front, size, border, sidelinesWidth, -rampHeight);

	/// Representa segmento vazio.
	case Empty:
	default:
		return ODETrackSegmentDefinition(vector< Side >(), ODETrackSegmentDefinition::Empty, false, Front, size, border, sidelinesWidth, 0);
	}
}



/// Constrói uma nova definição a partir de um vector de lados.
ODETrackSegmentDefinition::ODETrackSegmentDefinition(
	const vector< Side >& sides, Block type, bool isStartLine, Side startDirection
	, const ODEVector3 &size, ODEReal borderSize, ODEReal sidelinesWidth
	, ODEReal rampHeight)
{
	Init(sides, type, isStartLine, startDirection, size, borderSize, sidelinesWidth, rampHeight);
}



/// Constrói uma nova definição a partir de 2 lados.
ODETrackSegmentDefinition::ODETrackSegmentDefinition(
	Side side1, Side side2, Block type, bool isStartLine, Side startDirection
	, const ODEVector3 &size, ODEReal borderSize, ODEReal sidelinesWidth
	, ODEReal rampHeight)
{
	vector< Side > sides;

	sides.push_back(side1);
	sides.push_back(side2);
	Init(sides, type, isStartLine, startDirection, size, borderSize, sidelinesWidth, rampHeight);
}



/// Constrói uma nova definição a partir de outro.
ODETrackSegmentDefinition::ODETrackSegmentDefinition(const ODETrackSegmentDefinition &def)
{
	Init(def.sides, def.type, def.startLine, def.startDirection, def.size
		, def.borderSize, def.sidelinesWidth, def.rampHeight);
}



/// Constrói uma nova definição.
void ODETrackSegmentDefinition::Init(const vector< Side >& sides, Block type
	, bool isStartLine, Side startDirection, const ODEVector3 &size, ODEReal borderSize
	, ODEReal sidelinesWidth, ODEReal rampHeight)
{
	this->size = size;
	this->borderSize = borderSize;
	this->sides = sides;
	this->type = type;
	this->startLine = isStartLine;
	this->startDirection = startDirection;
	this->sidelinesWidth = sidelinesWidth;
	this->setGroundSurface(Gravel);
	this->setSidelinesSurface(Grass);
	this->rampHeight = rampHeight;
}



/// Destrói a definição.
ODETrackSegmentDefinition::~ODETrackSegmentDefinition()
{
}



/// Define as dimensões do bloco.
void ODETrackSegmentDefinition::setSize(const ODEVector3 &size)
{
	this->size = size;
}



/// Define a largura das paredes.
void ODETrackSegmentDefinition::setBorderSize(ODEReal border)
{
	this->borderSize = border;
}



/// Define a constituição dos lados.
void ODETrackSegmentDefinition::setSizes(vector< Side > sides)
{
	this->sides = sides;
}



/// Define o tipo de segmento.
void ODETrackSegmentDefinition::setType(Block block)
{
	this->type = block;
}



/// Define se o segmento é a meta.
void ODETrackSegmentDefinition::setStartLine(bool start)
{
	this->startLine = start;
}



/// Define a largura das partes de fora da pista.
void ODETrackSegmentDefinition::setSidelinesWidth(ODEReal width)
{
	this->sidelinesWidth = width;
}



/// Define o tipo de superfície do chão do segmento.
void ODETrackSegmentDefinition::setGroundSurface(Surface s)
{
	this->groundSurface = s;
	this->groundContact = getContactDefinition(s);
}



/// Define o tipo de superfície das partes laterais do segmento.
void ODETrackSegmentDefinition::setSidelinesSurface(Surface s)
{
	this->sidelinesSurface = s;
	this->sidelinesContact = getContactDefinition(s);
}



/// Altura da rampa.
void ODETrackSegmentDefinition::setRampHeight(ODEReal h)
{
	this->rampHeight = h;
}



/// Devolve as dimensões do bloco.
const ODEVector3& ODETrackSegmentDefinition::getSize() const
{
	return this->size;
}



/// Devolve a grossura das paredes.
ODEReal ODETrackSegmentDefinition::getBorderSize() const
{
	return this->borderSize;
}



/// Devolve a constituição dos lados.
const vector< ODETrackSegmentDefinition::Side >& ODETrackSegmentDefinition::getSides() const
{
	return this->sides;
}



/// Devolve o tipo de segmento.
ODETrackSegmentDefinition::Block ODETrackSegmentDefinition::getType() const
{
	return this->type;
}



/// Indica se o segmento contém a meta.
bool ODETrackSegmentDefinition::isStartLine() const
{
	return this->startLine;
}



/// Devolve a direcção da pista.
ODETrackSegmentDefinition::Side ODETrackSegmentDefinition::getStartDirection() const
{
	return this->startDirection;
}



/// Devolve o tamanho das partes laterais.
ODEReal ODETrackSegmentDefinition::getSidelinesWidth() const
{
	return this->sidelinesWidth;
}



/// Devolve as definições de contacto para o chão da pista.
const ODEContactDefinition& ODETrackSegmentDefinition::getGroundContact() const
{
	return this->groundContact;
}



/// Devolve as definições de contacto para as partes laterais da pista.
const ODEContactDefinition& ODETrackSegmentDefinition::getSidelinesContact() const
{
	return this->sidelinesContact;
}



/// Devolve o tipo de superfície do chão do segmento.
ODETrackSegmentDefinition::Surface ODETrackSegmentDefinition::getGroundSurface() const
{
	return this->groundSurface;
}



/// Devolve o tipo de superficie das partes laterais do segmento.
ODETrackSegmentDefinition::Surface ODETrackSegmentDefinition::getSidelinesSurface() const
{
	return this->sidelinesSurface;
}



/// Devolve definições de contacto para um tipo específico de superfície.
const ODEContactDefinition ODETrackSegmentDefinition::getContactDefinition(Surface s)
{
	switch (s)
	{
	case Grass:
		return ODEContactDefinition(
				1.5f	// mu
				, -1.0f// mu2
				, 15.0f	// bouncyness
				, -1	// velocityThreshold
				, -1	// erp
				, -1	// cfm
				, -1	// velocity
				, -1	// velocity2
				, -1// fds
				, -1);	// fds2

	case Snow:
		return ODEContactDefinition(
				1.0f	// mu
				, -1	// mu2
				, 10.0f	// bouncyness
				, -1	// velocityThreshold
				, -1	// erp
				, -1	// cfm
				, -1	// velocity
				, -1	// velocity2
				, 0.001f// fds
				, -1);	// fds2

	case Ice:
		return ODEContactDefinition(
				0.5f	// mu
				, -1.0f// mu2
				, -1.0f	// bouncyness
				, -1	// velocityThreshold
				, -1	// erp
				, -1	// cfm
				, -1	// velocity
				, -1	// velocity2
				, 0.001f// fds
				, -1);	// fds2

	case Gravel:
	default:
		return ODEContactDefinition(
				2.0f	// mu
				, -1	// mu2
				, -1	// bouncyness
				, -1	// velocityThreshold
				, -1	// erp
				, -1	// cfm
				, -1	// velocity
				, -1	// velocity2
				, -1	// fds
				, -1);	// fds2
	}
}



/// Devolve a altura da rampa
ODEReal ODETrackSegmentDefinition::getRampHeight() const
{
	return this->rampHeight;
}



/// Grava a definição do segmento para o stream.
/// Apenas grava tipo de segmento e tipo de superfície para chão e partes laterais.
/// (Para já isto é suficiente)
ostream& ODE::operator << (ostream& os, const ODE::ODETrackSegmentDefinition &t)
{
	os << (int)t.getType() << ";";
	os << (int)t.getGroundSurface() << ";";
	os << (int)t.getSidelinesSurface() << ";";

	return os;
}



/// Lê a definição do segmento do stream.
/// Apenas lê tipo de segmento e tipo de superfície para chão e partes laterais.
/// (Para já isto é suficiente)
istream& ODE::operator >> (istream& is, ODE::ODETrackSegmentDefinition &t)
{
	char c;
	int aux;

	is >> aux;
	is >> c;	// para ignorar ;
	t = ODETrackSegmentDefinition::get((ODE::ODETrackSegmentDefinition::Block)aux);
	is >> aux;
	is >> c;	// para ignorar ;
	t.setGroundSurface((ODE::ODETrackSegmentDefinition::Surface)aux);
	is >> aux;
	is >> c;	// para ignorar ;
	t.setSidelinesSurface((ODE::ODETrackSegmentDefinition::Surface)aux);

	return is;
}



/// Iguala um segmento a outro.
ODETrackSegmentDefinition& ODETrackSegmentDefinition::operator = (const ODETrackSegmentDefinition &t)
{
	Init(t.sides, t.type, t.startLine, t.startDirection, t.size
		, t.borderSize, t.sidelinesWidth, t.rampHeight);

	return *this;
}