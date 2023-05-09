#ifndef SliderJoint_h
#define SliderJoint_h

#include "Joint.h"

class SliderJoint : public Joint
{
	public:
		SliderJoint();
		SliderJoint(World &world);
		~SliderJoint();

		void SetAxis(XYZ xyz);
		double GetPosition() const;
		double GetPositionRate() const;
		void SetParameter(MotorParameter param, double value);
		double GetParameter(MotorParameter param);

	protected:
		void Init(World &world);
};

#endif