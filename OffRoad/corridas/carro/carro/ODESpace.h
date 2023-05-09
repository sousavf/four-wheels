#ifndef ODESPACE_H
#define ODESPACE_H

#include "ODERequirements.h"

namespace ODE
{
	/// Representa um espaço. Os corpos e geometrias são colocados em espaços.
	/// Os espaços servem para optimizar a simulação.
	class ODESpace
	{
	public:
		ODESpace(ODEWorld &world);
		ODESpace(ODEWorld &world, const ODESpace &space);
		~ODESpace();

		void add(const ODEGeometry &geom);
		void remove(const ODEGeometry &geom);
		bool contains(const ODEGeometry &geom) const;
		int count() const;
		dSpaceID getID() const;

	protected:
		dSpaceID id;
		ODEWorld *world;
	};
}

#endif