#ifndef Math_h
#define Math_h

class Math
{
	public:
		static const double PI;

		static double RandomDouble();
		static double RandomPercentage();
		static int RandomInt(int min, int max);
		static double RandomDouble(double min, double max);
		static double Min(double value1, double value2);
		static double Max(double value1, double value2);
		static double Round(double value, int digits);
		static double ToRadians(double degrees);
		static double ToDegrees(double radians);
};

#endif