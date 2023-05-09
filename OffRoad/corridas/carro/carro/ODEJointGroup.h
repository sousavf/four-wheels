#ifndef ODEJOINTGROUP_H
#define ODEJOINTGROUP_H

#include "ODERequirements.h"

namespace ODE
{
	/// Representa um grupo de juntas (articulações).
	class ODEJointGroup
	{
	public:
		ODEJointGroup(ODEWorld &world);
		~ODEJointGroup();

		void empty();

		dJointGroupID getID() const;

	protected:
		dJointGroupID id;
		ODEWorld *world;
	};
}

#endif