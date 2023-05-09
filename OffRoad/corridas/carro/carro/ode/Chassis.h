#ifndef Chassis_h
#define Chassis_h

#include "Object.h"

class Chassis : public Object
{
	public:
		Chassis(World &world, double mass, double width, double height, double length);
		~Chassis();
};

#endif