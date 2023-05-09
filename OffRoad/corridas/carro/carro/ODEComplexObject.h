#ifndef ODECOMPLEXOBJECT_H
#define ODECOMPLEXOBJECT_H

#include "ODERequirements.h"
#include <vector>

using namespace std;

namespace ODE
{
	/// Representa um objecto com um corpo e uma geometria.
	class ODEComplexObject : public ODEObject
	{
	public:
		ODEComplexObject(ODEWorld &world);
		~ODEComplexObject();

		virtual void setPosition(const ODEVector3 &pos) = 0;
		virtual void setRotation(const ODEMatrix3 &rot) = 0;
		virtual void setQuaternion(const ODEQuaternion &orientation) = 0;
		virtual void setLinearVelocity(const ODEVector3 &vel) = 0;
		virtual void setAngularVelocity(const ODEVector3 &vel) = 0;
        virtual void setForce(const ODEVector3 &force) = 0;
        virtual void setTorque(const ODEVector3 &torque) = 0;
		virtual void setCategoryBits(unsigned long bits) = 0;
		virtual void setCollideBits(unsigned long bits) = 0;

		virtual const ODEVector3 getPosition() const = 0;
		virtual const ODEMatrix3 getRotation() const = 0;
		virtual const ODEQuaternion getQuaternion() const = 0;
		virtual const ODEVector3 getLinearVelocity() const = 0;
		virtual const ODEVector3 getAngularVelocity() const = 0;
		virtual const ODEVector3 getForce() const = 0;
        virtual const ODEVector3 getTorque() const = 0;
		virtual unsigned long getCategoryBits() const = 0;
		virtual unsigned long getCollideBits() const = 0;

		virtual void addForce(const ODEVector3 &force) = 0;
		virtual void addTorque(const ODEVector3 &torque) = 0;
		virtual void addRelativeForce(const ODEVector3 &force) = 0;
		virtual void addRelativeTorque(const ODEVector3 &torque) = 0;
		virtual void addForceAtPosition(const ODEVector3 &force, const ODEVector3 &pos) = 0;
		virtual void addForceAtRelativePosition(const ODEVector3 &force, const ODEVector3 &pos) = 0;
		virtual void addRelativeForceAtPosition(const ODEVector3 &force, const ODEVector3 &pos) = 0;
		virtual void addRelativeForceAtRelativePosition(const ODEVector3 &force, const ODEVector3 &pos) = 0;

		virtual void setEnable(bool enable) = 0;
		virtual bool isEnabled() const = 0;
		const ODESpace& getSpace() const;
		virtual bool isAnyOf(const ODEGeometry &geom1, const ODEGeometry &geom2) const;
		virtual bool isAnyOf(const ODEGeometry *geom1, const ODEGeometry *geom2) const;

	protected:
		vector< ODESimpleObject* > objects;
		vector< ODEJoint* > joints;
		ODESpace space;
	};
}

#endif