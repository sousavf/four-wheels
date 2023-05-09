#include "ODEHeaders.h"

using namespace ODE;

/// Indica se a matriz de segmentos representa uma pista v�lida.
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



/// Indica se a coloca��o do segmento seg em x, y � v�lida.
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
			// se bloco vazio e n�o h� blocos em torno desse
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
				// se � bloco inicial, mas pista j� tem in�cio
				return false;
			}
			return true;
		}
		// se n�o � bloco inicial e est� isolado
		return false;
	}

	// � in�cio, mas j� h� in�cio (a menos que o outro in�cio esteja na mesma posi��o)
	if (start(block) && hasStart(segDefinitions, x, y))
	{
		return false;
	}

	// "vertical"
	if (straight(block))
	{
		// se tem frente ou tr�s (v�lidas)
		// e n�o tem segmentos que invalidem de lado
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
		// se tem esq. ou dir. (v�lidas)
		// e segmentos de topo e baixo n�o invalidam
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
		// se tem dir. ou baixo (v�lidas)
		// e segmento de topo e esq. n�o invalidam
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
		// se tem esq. ou baixo (v�lidas)
		// e segmento de topo e dir. n�o invalidam
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
		// se tem esq. ou baixo (v�lidos)
		// e blocos dir. e baixo n�o invalidam
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
		// se tem topo ou dir. v�lidos
		// e os segmentos � esq. ou baixo n�o invalidam
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



/// Indica se o bloco est� aberto � direita.
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



/// Indica se o bloco est� aberto � esquerda.
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



/// Indica se o bloco est� aberto � frente.
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



/// Indica se o bloco est� aberto em baixo.
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



/// Indica se o bloco est� fechado � direita.
bool ODETrackValidator::closeRight(ODETrackSegmentDefinition::Block b)
{
	return !openRight(b);
}



/// Indica se o bloco est� fechado � esquerda.
bool ODETrackValidator::closeLeft(ODETrackSegmentDefinition::Block b)
{
	return !openLeft(b);
}



/// Indica se o bloco est� fechado � frente.
bool ODETrackValidator::closeFront(ODETrackSegmentDefinition::Block b)
{
	return !openFront(b);
}



/// Indica se o bloco est� fechado em baixo.
bool ODETrackValidator::closeBack(ODETrackSegmentDefinition::Block b)
{
	return !openBack(b);
}



/// Indica se o bloco � uma recta "vertical".
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



/// Indica se o bloco � uma recta "horizontal".
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



/// Indica se o bloco � uma curva.
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



/// Indica se � um bloco vazio.
bool ODETrackValidator::empty(ODETrackSegmentDefinition::Block b)
{
	return (b == ODETrackSegmentDefinition::Empty);
}



/// Indica se o bloco � inicial (meta).
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



/// Indica se a matriz de blocos tem uma posi��o inicial.
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



/// Indica se tem in�cio, mas diferente de x, y.
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