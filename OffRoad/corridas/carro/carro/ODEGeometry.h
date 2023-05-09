#ifndef ODEGEOMETRY_H
#define ODEGEOMETRY_H

#include "ODERequirements.h"

namespace ODE
{
	/// Representa uma geometria. Uma geometria é usada para detecção de colisões.
	/// Usar as subclasses para geometrias específicas.
	class ODEGeometry
	{
	public:
		ODEGeometry(ODEWorld &world, const ODEContactDefinition &contactDef = ODEContactDefinition());
		~ODEGeometry();

		void setBody(const ODEBody &body);
		void setPosition(const ODEVector3 &pos);
		void setRotation(const ODEMatrix3 &rot);
		void setQuaternion(const ODEQuaternion &orientation);
		void setCategoryBits(unsigned long bits);
		void setCollideBits(unsigned long bits);

		ODEBody* getBody() const;
		const ODEVector3 getPosition() const;
		const ODEQuaternion getQuaternion() const;
		const ODEMatrix3 getRotation() const;
		unsigned long getCategoryBits() const;
		unsigned long getCollideBits() const;
		const ODEContactDefinition& getContactDefinition() const;

		void setEnable(bool enable);
		bool isEnabled() const;
		dGeomID getID() const;
		ODESpace& getSpace();
		bool hasBody() const;
		bool isAnyOf(const ODEGeometry &geom1, const ODEGeometry &geom2) const;
		bool isAnyOf(const ODEGeometry *geom1, const ODEGeometry *geom2) const;
		bool operator == (const ODEGeometry &geom) const;

	protected:
		dGeomID id;
		ODEWorld *world;
		ODEContactDefinition contactDefinition;

		void setData();
	};
}

#endif