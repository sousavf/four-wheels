#ifndef ChassisGeometry_h
#define ChassisGeometry_h

#include "BoxGeometry.h"

class ChassisGeometry : public BoxGeometry
{
	public:
		ChassisGeometry(const Space &space, double width, double height, double length, Color color);
		~ChassisGeometry();
};


#endif