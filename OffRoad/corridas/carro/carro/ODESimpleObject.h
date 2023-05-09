#ifndef ODESIMPLEOBJECT_H
#define ODESIMPLEOBJECT_H

#include "ODERequirements.h"

namespace ODE
{
	/// Representa um objecto com um corpo e uma geometria.
	class ODESimpleObject : public ODEObject
	{
	public:
		ODESimpleObject(ODEWorld &world);
		~ODESimpleObject();

		virtual void setPosition(const ODEVector3 &pos);
		virtual void setRotation(const ODEMatrix3 &rot);
		virtual void setQuaternion(const ODEQuaternion &orientation);
		virtual void setLinearVelocity(const ODEVector3 &vel);
		virtual void setAngularVelocity(const ODEVector3 &vel);
        virtual void setForce(const ODEVector3 &force);
        virtual void setTorque(const ODEVector3 &torque);
		virtual void setCategoryBits(unsigned long bits);
		virtual void setCollideBits(unsigned long bits);
		virtual void setMass(ODEReal mass) = 0;

		virtual const ODEVector3 getPosition() const;
		virtual const ODEMatrix3 getRotation() const;
		virtual const ODEQuaternion getQuaternion() const;
		virtual const ODEVector3 getLinearVelocity() const;
		virtual const ODEVector3 getAngularVelocity() const;
		virtual const ODEVector3 getForce() const;
        virtual const ODEVector3 getTorque() const;
		virtual unsigned long getCategoryBits() const;
		virtual unsigned long getCollideBits() const;
		virtual ODEReal getMass();

		virtual void addForce(const ODEVector3 &force);
		virtual void addTorque(const ODEVector3 &torque);
		virtual void addRelativeForce(const ODEVector3 &force);
		virtual void addRelativeTorque(const ODEVector3 &torque);
		virtual void addForceAtPosition(const ODEVector3 &force, const ODEVector3 &pos);
		virtual void addForceAtRelativePosition(const ODEVector3 &force, const ODEVector3 &pos);
		virtual void addRelativeForceAtPosition(const ODEVector3 &force, const ODEVector3 &pos);
		virtual void addRelativeForceAtRelativePosition(const ODEVector3 &force, const ODEVector3 &pos);

		virtual void setEnable(bool enable);
		virtual bool isEnabled() const;
		const ODESpace& getSpace() const;
		dGeomID getGeomID() const;
		dBodyID getBodyID() const;
		ODEBody& getBody();
		const ODEGeometry& getGeometry() const;
		virtual bool isAnyOf(const ODEGeometry &geom1, const ODEGeometry &geom2) const;
		virtual bool isAnyOf(const ODEGeometry *geom1, const ODEGeometry *geom2) const;

	protected:
		ODEBody body;
		ODEGeometry *geometry;
	};
}

#endif