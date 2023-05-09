#ifndef WheelGeometry_h
#define WheelGeometry_h

#include "SphereGeometry.h"

class WheelGeometry : public SphereGeometry
{
	public:
		WheelGeometry(const Space &space, double radius, double width);
		WheelGeometry(const Space &space, double radius, double width, Color color);
		~WheelGeometry();

		void Draw();

	protected:
		double radius;
		double width;

		void Init(const Space &space, double radius, double width, Color color);
};

#endif