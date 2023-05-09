#ifndef UTILITIES_H
#define UTILITIES_H

class Utilities
{
public:
	static double ToRadians(double degrees);
	static float ToRadians(float degrees);
	static double ToDegrees(double radians);
	static float ToDegrees(float radians);
	static int Random(int min, int max);
	static float Random(float min, float max);
	static float Random();
};

#endif