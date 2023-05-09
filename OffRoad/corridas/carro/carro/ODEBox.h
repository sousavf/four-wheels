#ifndef ODEBOX_H
#define ODEBOX_H

#include "ODERequirements.h"

namespace ODE
{
	/// Representa uma caixa.
	class ODEBox : public ODESimpleObject
	{
	public:
		ODEBox(ODEWorld &world, const ODESpace &space, ODEReal mass, const ODEVector3 &size
			, const ODEContactDefinition &contactDef = ODEContactDefinition());
		~ODEBox();

		void setSize(const ODEVector3 &size);
		void setMass(ODEReal mass);

		const ODEVector3 getSize() const;
	};
}

#endif