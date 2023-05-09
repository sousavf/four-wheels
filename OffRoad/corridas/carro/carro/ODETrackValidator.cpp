#include "ODEHeaders.h"

using namespace ODE;

/// Indica se a matriz de segmentos representa uma pista válida.
bool ODETrackValidator::isValid(const vector< vector< ODETrackSegmentDefinition > >& segDefinitions)
{
	if (!hasStart(segDefinitions))
	{
		return false;
	}

	for (int i = 0; i < (int)segDefinitions.size(); i++)
	{
		for (int j = 0; j < (int)segDefinitions[i].size(); j++)
		{
			if (!isValid(segDefinitions[i][j], j, i, segDefinitions))
			{
				return false;
			}
		}
	}

	return true;
}



/// Indica se a colocação do segmento seg em x, y é válida.
bool ODETrackValidator::isValid(const ODETrackSegmentDefinition &seg, int x, int y
	, const vector< vector< ODETrackSegmentDefinition > >& segDefinitions)
{
	bool hasLeft, hasRight, hasFront, hasBack, alone;
	ODETrackSegmentDefinition::Block blockLeft, blockRight, blockFront, blockBack, block;

	if ((int)segDefinitions.size() <= 0)
	{
		return false;
	}
	hasLeft = (x - 1 >= 0);
	hasRight = (x + 1 < (int)segDefinitions[0].size());
	hasFront = (y - 1 >= 0);
	hasBack = (y + 1 < (int)segDefinitions.size());
	blockLeft = (hasLeft ? segDefinitions[y][x - 1].getType() : ODETrackSegmentDefinition::Empty);
	blockRight = (hasRight ? segDefinitions[y][x + 1].getType() : ODETrackSegmentDefinition::Empty);
	blockFront = (hasFront ? segDefinitions[y - 1][x].getType() : ODETrackSegmentDefinition::Empty);
	blockBack = (hasBack ? segDefinitions[y + 1][x].getType() : ODETrackSegmentDefinition::Empty);
	block = seg.getType();
	alone = (empty(blockLeft) && empty(blockRight) && empty(blockFront) && empty(blockBack));

	// se bloco vazio
	if (empty(block))
	{
		if (alone)
		{
			// se bloco vazio e não há blocos em torno desse
			return true;
		}

		if ( (hasLeft && hasRight && openRight(blockLeft) && openLeft(blockRight))
			|| (hasFront && hasBack && openBack(blockFront) && openFront(blockBack))
			|| (hasLeft && hasBack && openFront(blockBack) && openRight(blockLeft))
			|| (hasRight && hasBack && openFront(blockBack) && openLeft(blockRight))
			|| (hasLeft && hasFront && openBack(blockFront) && openRight(blockLeft))
			|| (hasRight && hasFront && openBack(blockFront) && openLeft(blockRight)) )
		{
			// se vazio e quebrou pista
			return false;			
		}
		return true;
	}

	// se segmento isolado.
	if (alone && !empty(block))
	{
		if (start(block))
		{
			if (hasStart(segDefinitions))
			{
				// se é bloco inicial, mas pista já tem início
				return false;
			}
			return true;
		}
		// se não é bloco inicial e está isolado
		return false;
	}

	// é início, mas já há início (a menos que o outro início esteja na mesma posição)
	if (start(block) && hasStart(segDefinitions, x, y))
	{
		return false;
	}

	// "vertical"
	if (straight(block))
	{
		// se tem frente ou trás (válidas)
		// e não tem segmentos que invalidem de lado
		if ( ((hasFront && openBack(blockFront))
				|| (hasBack && openFront(blockBack)))
				&& ( (!hasFront || empty(blockFront) || (hasFront && !closeBack(blockFront)))
				&& (!hasBack || empty(blockBack) || (hasBack && !closeFront(blockBack)))
				&& (!hasLeft || empty(blockLeft) || (hasLeft && !openRight(blockLeft)))
				&& (!hasRight || empty(blockRight) || (hasRight && !openLeft(blockRight))) ))
		{
			return true;
		}
		return false;
	}
	
	// "horizontal"
	if (straightSide(block))
	{
		// se tem esq. ou dir. (válidas)
		// e segmentos de topo e baixo não invalidam
		if ( ((hasLeft && openRight(blockLeft))
			|| (hasRight && openLeft(blockRight)))
			&& ( (!hasLeft || empty(blockLeft) || (hasLeft && !closeRight(blockLeft)))
			&& (!hasRight || empty(blockRight) || (hasRight && !closeLeft(blockRight)))
			&& (!hasFront || empty(blockFront) || (hasFront && !openBack(blockFront)))
			&& (!hasBack || empty(blockBack) || (hasBack && !openFront(blockBack)))	))
		{
			return true;
		}
		return false;
	}
	
	// baixo para direita
	if (block == ODETrackSegmentDefinition::Curve90BottomToRight)
	{
		// se tem dir. ou baixo (válidas)
		// e segmento de topo e esq. não invalidam
		if ( ((hasRight && openLeft(blockRight))
			|| (hasBack && openFront(blockBack)))
			&& ( (!hasRight || empty(blockRight) || (hasRight && !closeLeft(blockRight)))
			&& (!hasBack || empty(blockBack) || (hasBack && !closeFront(blockBack)))
			&& (!hasFront || empty(blockFront) || (hasFront && !openBack(blockFront)))
			&& (!hasLeft || empty(blockLeft) || (hasLeft && !openRight(blockLeft)))	))
		{
			return true;
		}
		return false;
	}
	
	// esquerda para baixo
	if (block == ODETrackSegmentDefinition::Curve90LeftToBottom)
	{
		// se tem esq. ou baixo (válidas)
		// e segmento de topo e dir. não invalidam
		if ( ((hasLeft && openRight(blockLeft))
			|| (hasBack & openFront(blockBack)))
			&& ( (!hasLeft || empty(blockLeft) || (hasLeft && !closeRight(blockLeft)))
			&& (!hasBack || empty(blockBack) || (hasBack && !closeFront(blockBack)))
			&& (!hasFront || empty(blockFront) || (hasFront && !openBack(blockFront)))
			&& (!hasRight || empty(blockRight) || (hasRight && !openLeft(blockRight))) ))
		{
			return true;
		}
		return false;
	}
	
	// esquerda para topo
	if (block == ODETrackSegmentDefinition::Curve90LeftToTop)
	{
		// se tem esq. ou baixo (válidos)
		// e blocos dir. e baixo não invalidam
		if ( ((hasLeft && openRight(blockLeft))
			|| (hasFront && openBack(blockFront)))
			&& ( (!hasLeft || empty(blockLeft) || (hasLeft && !closeRight(blockLeft)))
			&& (!hasFront || empty(blockFront) || (hasFront && !closeBack(blockFront)))
			&& (!hasRight || empty(blockRight) || (hasRight && !openLeft(blockRight)))
			&& (!hasBack || empty(blockBack) || (hasBack && !openFront(blockBack)))	))
		{
			return true;
		}
		return false;
	}
	
	// topo para direita
	if (block == ODETrackSegmentDefinition::Curve90TopToRight)
	{
		// se tem topo ou dir. válidos
		// e os segmentos à esq. ou baixo não invalidam
		if ( ((hasFront && openBack(blockFront))
			|| (hasRight && openLeft(blockRight)))
			&& ( (!hasFront || empty(blockFront) || (hasFront && !closeBack(blockFront)))
			&& (!hasRight || empty(blockRight) || (hasRight && !closeLeft(blockRight)))
			&& (!hasBack || empty(blockBack) || (hasBack && !openFront(blockBack)))
			&& (!hasLeft || empty(blockLeft) || (hasLeft && !openRight(blockLeft))) ))
		{
			return true;
		}
		return false;
	}

	// desconhecido
	return false;
}



/// Indica se o bloco está aberto à direita.
bool ODETrackValidator::openRight(ODETrackSegmentDefinition::Block b)
{
	switch (b)
	{
	case ODETrackSegmentDefinition::RampStraightSideElevated:
	case ODETrackSegmentDefinition::RampStraightSideSunken:
	case ODETrackSegmentDefinition::StartStraightLeft:
	case ODETrackSegmentDefinition::StartStraightRight:
	case ODETrackSegmentDefinition::StraightSide:
	case ODETrackSegmentDefinition::Curve90BottomToRight:
	case ODETrackSegmentDefinition::Curve90TopToRight:
		return true;

	default:
		return false;
	}
}



/// Indica se o bloco está aberto à esquerda.
bool ODETrackValidator::openLeft(ODETrackSegmentDefinition::Block b)
{
	switch (b)
	{
	case ODETrackSegmentDefinition::RampStraightSideElevated:
	case ODETrackSegmentDefinition::RampStraightSideSunken:
	case ODETrackSegmentDefinition::StartStraightLeft:
	case ODETrackSegmentDefinition::StartStraightRight:
	case ODETrackSegmentDefinition::StraightSide:
	case ODETrackSegmentDefinition::Curve90LeftToBottom:
	case ODETrackSegmentDefinition::Curve90LeftToTop:
		return true;

	default:
		return false;
	}
}



/// Indica se o bloco está aberto à frente.
bool ODETrackValidator::openFront(ODETrackSegmentDefinition::Block b)
{
	switch (b)
	{
	case ODETrackSegmentDefinition::RampStraightElevated:
	case ODETrackSegmentDefinition::RampStraightSunken:
	case ODETrackSegmentDefinition::StartStraightBack:
	case ODETrackSegmentDefinition::StartStraightFront:
	case ODETrackSegmentDefinition::Straight:
	case ODETrackSegmentDefinition::Curve90LeftToTop:
	case ODETrackSegmentDefinition::Curve90TopToRight:
		return true;

	default:
		return false;
	}
}



/// Indica se o bloco está aberto em baixo.
bool ODETrackValidator::openBack(ODETrackSegmentDefinition::Block b)
{
	switch (b)
	{
	case ODETrackSegmentDefinition::RampStraightElevated:
	case ODETrackSegmentDefinition::RampStraightSunken:
	case ODETrackSegmentDefinition::StartStraightBack:
	case ODETrackSegmentDefinition::StartStraightFront:
	case ODETrackSegmentDefinition::Straight:
	case ODETrackSegmentDefinition::Curve90BottomToRight:
	case ODETrackSegmentDefinition::Curve90LeftToBottom:
		return true;

	default:
		return false;
	}
}



/// Indica se o bloco está fechado à direita.
bool ODETrackValidator::closeRight(ODETrackSegmentDefinition::Block b)
{
	return !openRight(b);
}



/// Indica se o bloco está fechado à esquerda.
bool ODETrackValidator::closeLeft(ODETrackSegmentDefinition::Block b)
{
	return !openLeft(b);
}



/// Indica se o bloco está fechado à frente.
bool ODETrackValidator::closeFront(ODETrackSegmentDefinition::Block b)
{
	return !openFront(b);
}



/// Indica se o bloco está fechado em baixo.
bool ODETrackValidator::closeBack(ODETrackSegmentDefinition::Block b)
{
	return !openBack(b);
}



/// Indica se o bloco é uma recta "vertical".
bool ODETrackValidator::straight(ODETrackSegmentDefinition::Block b)
{
	switch (b)
	{
	case ODETrackSegmentDefinition::RampStraightElevated:
	case ODETrackSegmentDefinition::RampStraightSunken:
	case ODETrackSegmentDefinition::StartStraightBack:
	case ODETrackSegmentDefinition::StartStraightFront:
	case ODETrackSegmentDefinition::Straight:
		return true;

	default:
		return false;
	}
}



/// Indica se o bloco é uma recta "horizontal".
bool ODETrackValidator::straightSide(ODETrackSegmentDefinition::Block b)
{
	switch (b)
	{
	case ODETrackSegmentDefinition::RampStraightSideElevated:
	case ODETrackSegmentDefinition::RampStraightSideSunken:
	case ODETrackSegmentDefinition::StartStraightLeft:
	case ODETrackSegmentDefinition::StartStraightRight:
	case ODETrackSegmentDefinition::StraightSide:
		return true;

	default:
		return false;
	}
}



/// Indica se o bloco é uma curva.
bool ODETrackValidator::curve(ODETrackSegmentDefinition::Block b)
{
	switch (b)
	{
	case ODETrackSegmentDefinition::Curve90BottomToRight:
	case ODETrackSegmentDefinition::Curve90LeftToBottom:
	case ODETrackSegmentDefinition::Curve90LeftToTop:
	case ODETrackSegmentDefinition::Curve90TopToRight:
		return true;

	default:
		return false;
	}
}



/// Indica se é um bloco vazio.
bool ODETrackValidator::empty(ODETrackSegmentDefinition::Block b)
{
	return (b == ODETrackSegmentDefinition::Empty);
}



/// Indica se o bloco é inicial (meta).
bool ODETrackValidator::start(ODETrackSegmentDefinition::Block b)
{
	switch (b)
	{
	case ODETrackSegmentDefinition::StartStraightBack:
	case ODETrackSegmentDefinition::StartStraightFront:
	case ODETrackSegmentDefinition::StartStraightLeft:
	case ODETrackSegmentDefinition::StartStraightRight:
		return true;

	default:
		return false;
	}
}



/// Indica se a matriz de blocos tem uma posição inicial.
bool ODETrackValidator::hasStart(const vector< vector< ODETrackSegmentDefinition > >& segDefinitions)
{
	for (int i = 0; i < (int)segDefinitions.size(); i++)
	{
		for (int j = 0; j < (int)segDefinitions[i].size(); j++)
		{
			if (start(segDefinitions[i][j].getType()))
			{
				return true;
			}
		}
	}

	return false;
}



/// Indica se tem início, mas diferente de x, y.
bool ODETrackValidator::hasStart(const vector< vector< ODETrackSegmentDefinition > >& segDefinitions
			, int x, int y)
{
	for (int i = 0; i < (int)segDefinitions.size(); i++)
	{
		for (int j = 0; j < (int)segDefinitions[i].size(); j++)
		{
			if ( start(segDefinitions[i][j].getType())
				&& ((x != j) || (y != i)) )
			{
				return true;
			}
		}
	}

	return false;
}