#ifndef Wheel_h
#define Wheel_h

#include "Object.h"

class Wheel : public Object
{
	friend class Car;
	friend class SoccerRobot;

	public:
		Wheel();
		Wheel(World &world, double mass, double radius, double width);
		~Wheel();

	protected:
		void Init(World &world, double mass, double radius, double width);
		void Prepare();

};

#endif