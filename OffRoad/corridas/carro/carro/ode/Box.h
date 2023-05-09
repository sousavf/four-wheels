#ifndef Box_h
#define Box_h

#include "Object.h"

class Box : public Object
{
	public:
		Box(World &world, double mass, double size);
		Box(World &world, double mass, double width, double height, double length);
		Box(World &world, double mass, double width, double height, double length, bool addToWorld);
		~Box();

	protected:
		void Init(World &world, double mass, double width, double height, double length, bool addToWorld);
};

#endif