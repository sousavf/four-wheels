#ifndef FixedJoint_h
#define FixedJoint_h

#include "Joint.h"
#include "World.h"

class FixedJoint : public Joint
{
	public:
		FixedJoint();
		FixedJoint(World &world);
		~FixedJoint();

		void SetFixed();

	protected:
		void Init(World &world);
};

#endif