#ifndef Cylinder_h
#define Cylinder_h

#include "Object.h"

class Cylinder : public Object
{
	public:
		Cylinder(World &world, double mass, double radius, double length);
		~Cylinder();

	protected:
		void Init(World &world, double mass, double radius, double length);
};

#endif