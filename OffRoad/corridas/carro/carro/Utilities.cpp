#include "Utilities.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <stdlib.h>

/// Devolve o valor respectivo em radianos.
double Utilities::ToRadians(double degrees)
{
	return (degrees / 180) * M_PI;
}



/// Devolve o valor respectivo em radianos.
float Utilities::ToRadians(float degrees)
{
	return (degrees / 180) * (float)M_PI;
}



/// Devolve o valor respect5ivo em graus.
double Utilities::ToDegrees(double radians)
{
	return (radians / M_PI) * 180;
}



/// Devolve o valor respectivo em graus.
float Utilities::ToDegrees(float radians)
{
	return (radians / (float)M_PI) * 180;
}



/// Devolve um inteiro entre min e max (inclusivé).
int Utilities::Random(int min, int max)
{
	return ( min + (int)((max - min) * Random()) );
}



/// Devolve um float entre min e max (inclusivé).
float Utilities::Random(float min, float max)
{
	return ( min + (max - min) * Random() );
}



/// Devolve um float entre 0 e 1 (inclusivé).
float Utilities::Random()
{
	return ( (float)rand() / (float)RAND_MAX );
}