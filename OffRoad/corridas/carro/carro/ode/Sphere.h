#ifndef Sphere_h
#define Sphere_h

#include "Object.h"

class Sphere : public Object
{
	public:
		Sphere(World &world, double mass, double radius);
		Sphere(World &world, double mass, double radius, bool bounce);
		~Sphere();

	protected:
		void Init(World &world, double mass, double radius, bool bounce);
};

#endif