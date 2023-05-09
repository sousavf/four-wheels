#include "Math.h"
#include <ode/ode.h>
#include <stdlib.h>
#include <math.h>

const double Math::PI = M_PI;

/// Devolve um valor de -1 a 1.
double Math::RandomDouble()
{
	return RandomPercentage() - RandomPercentage();
}



/// Devolve um valor de 0 a 1.
double Math::RandomPercentage()
{
	return ( (double)rand() / (double)RAND_MAX );
}



/// Devolve um inteiro entre min e max.
int Math::RandomInt(int min, int max)
{
	return (min + (int)( (max - min + 1) * rand() / (RAND_MAX + 1.0) ));//(rand() % max + min);
}



/// Devolve um double entre min e max.
double Math::RandomDouble(double min, double max)
{
	return ( ((max - min) * RandomPercentage()) + min );
}



/// Devolve a distância (Euclideana) entre dois pontos.
double Math::Min(double value1, double value2)
{
	return (value1 < value2) ? value1 : value2;
}



/// Devolve o maior dos 2 valores.
double Math::Max(double value1, double value2)
{
	return (value1 > value2) ? value1 : value2;
}



/// Devolve value arredondado a digits casas decimais.
double Math::Round(double value, int digits)
{
    int modifier = 1;

    for (int i = 0; i < digits; i++)
	{
        modifier *= 10;
	}

    if (value < 0.0)
	{
        return (ceil(value * modifier - 0.5) / modifier);
	}

    return (floor(value * modifier + 0.5) / modifier);
}



/// Dado um valor em graus devolve a correspondência em radianos.
double Math::ToRadians(double degrees)
{
	return (degrees * PI) / 180.0;
}



/// Dado um valor em radianos devolve a correspondência em graus.
double Math::ToDegrees(double radians)
{
	return (radians * 180.0) / PI;
}
