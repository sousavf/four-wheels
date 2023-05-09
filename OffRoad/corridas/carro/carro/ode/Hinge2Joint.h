#ifndef Hinge2Joint_h
#define Hinge2Joint_h

#include "Joint.h"

class Hinge2Joint : public Joint
{
	public:
		Hinge2Joint();
		Hinge2Joint(World &world);
		~Hinge2Joint();

		void SetAnchor(XYZ xyz);
		void SetAxis1(XYZ xyz);
		void SetAxis2(XYZ xyz);
		double GetAngle1();
		double GetAngle1Rate();
		double GetAngle2Rate();
		void SetParameter(MotorParameter param, double value);
		double GetParameter(MotorParameter param);

	protected:
		void Init(World &world);
};

#endif