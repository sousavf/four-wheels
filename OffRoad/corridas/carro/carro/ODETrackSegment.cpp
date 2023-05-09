#include "ODEHeaders.h"

using namespace ODE;

/// Constrói um segmento.
ODETrackSegment::ODETrackSegment(ODEWorld &world, const ODESpace &space
	, ODETrackSegmentDefinition &def, const ODEVector3 &position)
	:definition(def)
{
	this->position = position;
	this->ground.push_back(new ODEBoxGeometry(world, space, groundSize(), def.getGroundContact()));
	this->ground[0]->setPosition(groundPosition());

	for (int i = 0; i < (int)def.getSides().size(); i++)
	{
		this->sides.push_back(newSide(world, space, def.getSides()[i]));
		this->ground.push_back(newGround(world, space, def.getSides()[i]));
	}

	switch (this->definition.getType())
	{
	case ODETrackSegmentDefinition::RampStraightElevated:
	case ODETrackSegmentDefinition::RampStraightSunken:
	case ODETrackSegmentDefinition::RampStraightSideElevated:
	case ODETrackSegmentDefinition::RampStraightSideSunken:
		this->ground.push_back(new ODEBoxGeometry(world, space, groundSize(), def.getGroundContact()));
		this->ground[(int)this->ground.size() - 1]->setPosition(groundPosition());

		for (int i = 0; i < (int)def.getSides().size(); i++)
		{
			this->ground.push_back(newGround(world, space, def.getSides()[i]));
		}

		for (int i = 0, r = 0; i < (int)this->ground.size(); i++)
		{
			if (i >= 0.5f * (int)this->ground.size())
			{
				r = 1;
			}
			this->ground[i]->setPosition(rampPosition(this->ground[i]->getPosition(), r));
			this->ground[i]->setQuaternion(rampQuaternion(r));
		}
		
		break;
	}
}



/// Destrói o segmento.
ODETrackSegment::~ODETrackSegment()
{
	while (!this->sides.empty())
	{
		this->sides[0]->~ODEBoxGeometry();
		this->sides.erase(this->sides.begin());
	}

	while (!this->ground.empty())
	{
		this->ground[0]->~ODEBoxGeometry();
		this->ground.erase(this->ground.begin());
	}
}



/// Devolve um quaternion respectivo à rampa r (uma rampa tem sempre 2 partes - subida e descida).
const ODEQuaternion ODETrackSegment::rampQuaternion(int r) const
{
	ODEQuaternion q;
	ODEReal angle = rampAngle(r);

	switch (this->definition.getType())
	{
	case ODETrackSegmentDefinition::RampStraightElevated:
	case ODETrackSegmentDefinition::RampStraightSunken:
		q.fromAxisAndAngle(1, 0, 0, angle);
		break;

	case ODETrackSegmentDefinition::RampStraightSideElevated:
	case ODETrackSegmentDefinition::RampStraightSideSunken:
		q.fromAxisAndAngle(0, 1, 0, angle);
		break;
	}

	return q;
}



/// Devolve o ângulo respectivo à rampa r (uma rampa tem sempre 2 partes - subida e descida) - em radianos.
ODEReal ODETrackSegment::rampAngle(int r) const
{
	ODEReal size, h;
	int m = (r == 0 ? 1 : -1);

	switch (this->definition.getType())
	{
	case ODETrackSegmentDefinition::RampStraightElevated:
	case ODETrackSegmentDefinition::RampStraightSunken:
		size = 0.5f * this->definition.getSize()[1];
		break;

	case ODETrackSegmentDefinition::RampStraightSideElevated:
	case ODETrackSegmentDefinition::RampStraightSideSunken:
		size = 0.5f * this->definition.getSize()[0];
		m *= -1;
		break;

	default:
		return 0;
	}

	switch (this->definition.getType())
	{
	case ODETrackSegmentDefinition::RampStraightSunken:
	case ODETrackSegmentDefinition::RampStraightSideSunken:
		m *= -1;
		break;
	}
	h = sqrt( pow(size, 2) + pow(this->definition.getRampHeight(), 2) );

	return m * acosf(size / h);
}



/// Devolve a posição para a rampa r (uma rampa tem sempre 2 partes - subida e descida) e a posição
/// anterior da rampa.
const ODEVector3 ODETrackSegment::rampPosition(const ODEVector3 &pos, int r) const
{
	ODEVector3 newPos(pos);
	int m = (r == 0 ? -1 : 1);

	switch (this->definition.getType())
	{
	case ODETrackSegmentDefinition::RampStraightElevated:
	case ODETrackSegmentDefinition::RampStraightSunken:
		newPos[1] = pos[1] + m * 0.25f * this->definition.getSize()[1];
		break;

	case ODETrackSegmentDefinition::RampStraightSideElevated:
	case ODETrackSegmentDefinition::RampStraightSideSunken:
		newPos[0] = pos[0] + m * 0.25f * this->definition.getSize()[0];
		break;
	}
	newPos[2] = pos[2] + 0.5f * this->definition.getRampHeight();

	return newPos;
}



/// Constrói uma nova parte lateral da pista.
ODEBoxGeometry* ODETrackSegment::newGround(ODEWorld &world, const ODESpace &space
			, ODETrackSegmentDefinition::Side side)
{
	ODEBoxGeometry *g;

	g = new ODEBoxGeometry(world, space, sidelineSize(side), this->definition.getSidelinesContact());
	g->setPosition(sidelinePosition(side));
	
	return g;
}



/// Devolve o tamanho que o chão deverá ter.
const ODEVector3 ODETrackSegment::groundSize()
{
	ODEReal size, height;

	switch (this->definition.getType())
	{
	case ODETrackSegmentDefinition::StartStraightBack:
	case ODETrackSegmentDefinition::StartStraightFront:
	case ODETrackSegmentDefinition::Straight:
		return ODEVector3(
			this->definition.getSize()[0] - 2 * this->definition.getSidelinesWidth()
			, this->definition.getSize()[1]
			, this->definition.getBorderSize());

	case ODETrackSegmentDefinition::RampStraightElevated:
	case ODETrackSegmentDefinition::RampStraightSunken:
		size = 0.5f * this->definition.getSize()[1];
		height = this->definition.getRampHeight();

		return ODEVector3(
			this->definition.getSize()[0] - 2 * this->definition.getSidelinesWidth()
			, sqrt( pow(size, 2) + pow(height, 2) )
			, this->definition.getBorderSize());

	case ODETrackSegmentDefinition::RampStraightSideElevated:
	case ODETrackSegmentDefinition::RampStraightSideSunken:
		size = 0.5f * this->definition.getSize()[0];
		height = this->definition.getRampHeight();

		return ODEVector3(
			sqrt( pow(size, 2) + pow(height, 2) )
			, this->definition.getSize()[1] - 2 * this->definition.getSidelinesWidth()
			, this->definition.getBorderSize());

	case ODETrackSegmentDefinition::StartStraightLeft:
	case ODETrackSegmentDefinition::StartStraightRight:
	case ODETrackSegmentDefinition::StraightSide:
		return ODEVector3(this->definition.getSize()[0]
			, this->definition.getSize()[1] - 2 * this->definition.getSidelinesWidth()
			, this->definition.getBorderSize());

	case ODETrackSegmentDefinition::Curve90BottomToRight:
	case ODETrackSegmentDefinition::Curve90LeftToBottom:
	case ODETrackSegmentDefinition::Curve90LeftToTop:
	case ODETrackSegmentDefinition::Curve90TopToRight:
		return ODEVector3(
			this->definition.getSize()[0] - this->definition.getSidelinesWidth()
			, this->definition.getSize()[1] - this->definition.getSidelinesWidth()
			, this->definition.getBorderSize());

	default:
		return ODEVector3();
	}
}



/// Devolve a posição do chão.
const ODEVector3 ODETrackSegment::groundPosition() const
{
	ODEReal offset;

	offset = 0.5f * this->definition.getSidelinesWidth();

	switch (this->definition.getType())
	{
	case ODETrackSegmentDefinition::Curve90BottomToRight:
		return ODEVector3(this->position[0] + offset
			, this->position[1] + offset
			, this->position[2]);

	case ODETrackSegmentDefinition::Curve90LeftToBottom:
		return ODEVector3(this->position[0] - offset
			, this->position[1] + offset
			, this->position[2]);

	case ODETrackSegmentDefinition::Curve90LeftToTop:
		return ODEVector3(this->position[0] - offset
			, this->position[1] - offset
			, this->position[2]);

	case ODETrackSegmentDefinition::Curve90TopToRight:
		return ODEVector3(this->position[0] + offset
			, this->position[1] - offset
			, this->position[2]);

	default:
	case ODETrackSegmentDefinition::StartStraightBack:
	case ODETrackSegmentDefinition::StartStraightFront:
	case ODETrackSegmentDefinition::Straight:
	case ODETrackSegmentDefinition::StartStraightLeft:
	case ODETrackSegmentDefinition::StartStraightRight:
	case ODETrackSegmentDefinition::StraightSide:
	case ODETrackSegmentDefinition::RampStraightElevated:
	case ODETrackSegmentDefinition::RampStraightSunken:
	case ODETrackSegmentDefinition::RampStraightSideElevated:
	case ODETrackSegmentDefinition::RampStraightSideSunken:
		return this->position;
	}
}



/// Indica o tamanho de uma parte lateral do chão.
const ODEVector3 ODETrackSegment::sidelineSize(ODETrackSegmentDefinition::Side side)
{
	ODEVector3 gSize;
	int axis;

	gSize = this->definition.getSize();

	switch (this->definition.getType())
	{
	case ODETrackSegmentDefinition::RampStraightElevated:
	case ODETrackSegmentDefinition::RampStraightSunken:
		gSize[1] = this->ground[0]->getSize()[1];
		break;

	case ODETrackSegmentDefinition::RampStraightSideElevated:
	case ODETrackSegmentDefinition::RampStraightSideSunken:
		gSize[0] = this->ground[0]->getSize()[0];
		break;
	}

	switch (this->definition.getType())
	{
	case ODETrackSegmentDefinition::Straight:
	case ODETrackSegmentDefinition::StartStraightBack:
	case ODETrackSegmentDefinition::StartStraightFront:
	case ODETrackSegmentDefinition::RampStraightElevated:
	case ODETrackSegmentDefinition::RampStraightSunken:
		axis = 0;
		break;

	case ODETrackSegmentDefinition::StraightSide:
	case ODETrackSegmentDefinition::StartStraightLeft:
	case ODETrackSegmentDefinition::StartStraightRight:
	case ODETrackSegmentDefinition::RampStraightSideElevated:
	case ODETrackSegmentDefinition::RampStraightSideSunken:
		axis = 1;
		break;

	case ODETrackSegmentDefinition::Curve90BottomToRight:
		switch (side)
		{
		case ODETrackSegmentDefinition::Left:
			axis = 0;
			break;

		case ODETrackSegmentDefinition::Front:
			axis = 1;
			break;
		}
		break;

	case ODETrackSegmentDefinition::Curve90LeftToBottom:
		switch (side)
		{
		case ODETrackSegmentDefinition::Right:
			axis = 0;
			break;

		case ODETrackSegmentDefinition::Front:
			axis = 1;
			break;
		}
		break;

	case ODETrackSegmentDefinition::Curve90LeftToTop:
		switch (side)
		{
		case ODETrackSegmentDefinition::Right:
			axis = 0;
			break;

		case ODETrackSegmentDefinition::Back:
			axis = 1;
			break;
		}
		break;

	case ODETrackSegmentDefinition::Curve90TopToRight:
		switch (side)
		{
		case ODETrackSegmentDefinition::Left:
			axis = 0;
			break;

		case ODETrackSegmentDefinition::Back:
			axis = 1;
			break;
		}
		break;

	default:
		return ODEVector3();
	}
	gSize[axis] = this->definition.getSidelinesWidth();
	gSize[2] = this->definition.getBorderSize();

	return gSize;
}



/// Indica a posição onde vai a parte lateral do chão.
const ODEVector3 ODETrackSegment::sidelinePosition(ODETrackSegmentDefinition::Side side)
{
	ODEVector3 gPosition;
	ODEReal groundSize, borderSize;
	int axis, mult;

	groundSize = this->definition.getSize()[0] - 2 * this->definition.getSidelinesWidth();
	borderSize = this->definition.getBorderSize();
	gPosition = this->position;

	switch (this->definition.getType())
	{
	case ODETrackSegmentDefinition::Straight:
	case ODETrackSegmentDefinition::StartStraightBack:
	case ODETrackSegmentDefinition::StartStraightFront:
	case ODETrackSegmentDefinition::RampStraightElevated:
	case ODETrackSegmentDefinition::RampStraightSunken:
		switch (side)
		{
		case ODETrackSegmentDefinition::Left:
			mult = -1;
			break;

		case ODETrackSegmentDefinition::Right:
			mult = 1;
			break;
		}
		axis = 0;
		break;

	case ODETrackSegmentDefinition::StraightSide:
	case ODETrackSegmentDefinition::StartStraightLeft:
	case ODETrackSegmentDefinition::StartStraightRight:
	case ODETrackSegmentDefinition::RampStraightSideElevated:
	case ODETrackSegmentDefinition::RampStraightSideSunken:
		switch (side)
		{
		case ODETrackSegmentDefinition::Front:
			mult = -1;
			break;

		case ODETrackSegmentDefinition::Back:
			mult = 1;
			break;
		}
		axis = 1;
		break;

	case ODETrackSegmentDefinition::Curve90BottomToRight:
		switch (side)
		{
		case ODETrackSegmentDefinition::Left:
			mult = -1;
			axis = 0;
			break;

		case ODETrackSegmentDefinition::Front:
			mult = -1;
			axis = 1;
			break;
		}
		break;

	case ODETrackSegmentDefinition::Curve90LeftToBottom:
		switch (side)
		{
		case ODETrackSegmentDefinition::Right:
			mult = 1;
			axis = 0;
			break;

		case ODETrackSegmentDefinition::Front:
			mult = -1;
			axis = 1;
			break;
		}
		break;

	case ODETrackSegmentDefinition::Curve90LeftToTop:
		switch (side)
		{
		case ODETrackSegmentDefinition::Right:
			mult = 1;
			axis = 0;
			break;

		case ODETrackSegmentDefinition::Back:
			mult = 1;
			axis = 1;
			break;
		}
		break;

	case ODETrackSegmentDefinition::Curve90TopToRight:
		switch (side)
		{
		case ODETrackSegmentDefinition::Left:
			mult = -1;
			axis = 0;
			break;

		case ODETrackSegmentDefinition::Back:
			mult = 1;
			axis = 1;
			break;
		}
		break;

	default:
		return ODEVector3();
	}
	gPosition[axis] += mult * (0.5f * groundSize + 0.5f * this->definition.getSidelinesWidth()); 
	gPosition[2] += 0.5f * borderSize;

	return gPosition;
}



/// Constrói um novo lado.
ODEBoxGeometry* ODETrackSegment::newSide(ODEWorld &world, const ODESpace &space
	, ODETrackSegmentDefinition::Side side)
{
	ODEBoxGeometry *boxSide;
	ODEVector3 sideSize, sidePosition, size;
	ODEReal borderSize;

	size = this->definition.getSize();
	sideSize = this->definition.getSize();
	sidePosition = this->position;
	borderSize = this->definition.getBorderSize();

	switch (side)
	{
	case ODETrackSegmentDefinition::Front:
		sideSize[1] = borderSize;
		sidePosition[1] -= 0.5f * size[1] - 0.5f * sideSize[1];
		break;

	case ODETrackSegmentDefinition::Right:
		sideSize[0] = borderSize;
		sidePosition[0] += 0.5f * size[0] + 0.5f * sideSize[0];
		break;

	case ODETrackSegmentDefinition::Back:
		sideSize[1] = borderSize;
		sidePosition[1] += 0.5f * size[1] + 0.5f * sideSize[1];
		break;

	case ODETrackSegmentDefinition::Left:
		sideSize[0] = borderSize;
		sidePosition[0] -= 0.5f * size[0] - 0.5f * sideSize[0];
		break;
	}
	sidePosition[2] += 0.5f * borderSize;
	boxSide = new ODEBoxGeometry(world, space, sideSize);
	boxSide->setPosition(sidePosition);

	return boxSide;
}



/// Define a posição do segmento. O chão é a referência.
void ODETrackSegment::setPosition(const ODEVector3 &p)
{
	this->position = p;
	this->ground[0]->setPosition(groundPosition());

	for (int i = 0; i < (int)this->sides.size(); i++)
	{
		this->sides[i]->setPosition(sidePosition(this->definition.getSides()[i]));
		this->ground[i + 1]->setPosition(sidelinePosition(this->definition.getSides()[i]));
	}
}



/// Devolve a posição para um lado específico.
const ODEVector3 ODETrackSegment::sidePosition(ODETrackSegmentDefinition::Side side)
{
	ODEVector3 position, size;
	ODEReal borderSize;
	int axis, sign;

	size = this->definition.getSize();
	borderSize = this->definition.getBorderSize();
	position = this->position;
	sign = 1;
	axis = 0;

	switch (side)
	{
	case ODETrackSegmentDefinition::Front:
		axis = 1;
		sign = -1;
		break;

	case ODETrackSegmentDefinition::Right:
		axis = 0;
		sign = 1;
		break;

	case ODETrackSegmentDefinition::Back:
		axis = 1;
		sign = 1;
		break;

	case ODETrackSegmentDefinition::Left:
		axis = 0;
		sign = -1;
		break;
	}
	position[axis] = sign * (0.5f * size[axis] + 0.5f * borderSize);
	position[2] += 0.5f * borderSize;

	return position;
}



/// Devolve a posição do segmento.
const ODEVector3& ODETrackSegment::getPosition() const
{
	return this->position;
}



/// Devolve o tamanho do segmento.
const ODEVector3& ODETrackSegment::getSize() const
{
	return this->definition.getSize();
}



/// Devolve a grossura das paredes.
ODEReal ODETrackSegment::getBorderSize() const
{
	return this->definition.getBorderSize();
}



/// Devolve o chão.
const ODEBoxGeometry& ODETrackSegment::getGround(int index) const
{
	return *(this->ground[index]);
}



/// Devolve o nr. de paredes que tem.
int ODETrackSegment::sidesCount() const
{
	return (int)this->sides.size();
}



/// Devolve a parede correspondente a index.
const ODEBoxGeometry& ODETrackSegment::getSide(int index) const
{
	return *(this->sides[index]);
}



/// Devolve o tipo de bloco.
const ODETrackSegmentDefinition::Block ODETrackSegment::getType() const
{
	return this->definition.getType();
}



/// Devolve o tipo de superfície do chão do segmento.
ODETrackSegmentDefinition::Surface ODETrackSegment::getGroundSurface() const
{
	return this->definition.getGroundSurface();
}



/// Devolve o tipo de superficie das partes laterais do segmento.
ODETrackSegmentDefinition::Surface ODETrackSegment::getSidelinesSurface() const
{
	return this->definition.getSidelinesSurface();
}



/// Devolve a definição do segmento.
ODETrackSegmentDefinition ODETrackSegment::getDefinition() const
{
	return this->definition;
}