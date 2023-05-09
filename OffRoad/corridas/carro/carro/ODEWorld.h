#ifndef ODEWORLD_H
#define ODEWORLD_H

#include "ODERequirements.h"

namespace ODE
{
	/// A classe que governa o mundo do ODE.
	class ODEWorld
	{
	public:
		typedef bool (*createContactDelegate)(ODEContact&, ODEGeometry*, ODEGeometry*);

		ODEWorld();
		ODEWorld(const ODEVector3 &gravity);
		ODEWorld(ODEReal gravityZ);
		~ODEWorld();

		void setGravity(const ODEVector3 &g);
		void setERP(ODEReal erp);
		void setCFM(ODEReal cfm);
		void setAutoDisable(bool doAutoDisable);
		void setAutoDisableLinearThreshold(ODEReal linearThreshold);
		void setAutoDisableAngularThreshold(ODEReal angularThreshold);
		void setAutoDisableSteps(int steps);
		void setAutoDisableTime(ODEReal time);
		void setContactSurfaceLayer(ODEReal depth);
		void setLinearDampening(ODEReal damp);
		void setAngularDampening(ODEReal damp);
		void setStepTime(ODEReal miliseconds);
		void setMaxContacts(int max);
		void setStepIterations(int n);
		void setCreateContact(createContactDelegate ccDelegate);
		void setContactMaxCorrectingVelocity(ODEReal max);
		void setApplyDampening(bool apply);

		const ODEVector3 getGravity() const;
		ODEReal getERP() const;
		ODEReal getCFM() const;
		bool getAutoDisable() const;
		ODEReal getAutoDisableLinearThreshold() const;
		ODEReal getAutoDisableAngularThreshold() const;
		int getAutoDisableSteps() const;
		ODEReal getAutoDisableTime() const;
		ODEReal getContactSurfaceLayer() const;
		ODEReal getLinearDampening() const;
		ODEReal getAngularDampening() const;
		ODEReal getStepTime() const;
		int getMaxContacts() const;
		int getStepIterations() const;
		createContactDelegate getCreateContact() const;
		ODEReal getContactMaxCorrectingVelocity() const;
		bool getApplyDampening() const;

		void step();
		dWorldID getID() const;
		const ODESpace& getSpace() const;
		const ODEJointGroup& getContactsGroup();

	protected:
		static ODEWorld *currentWorld;

		static void nearCallback(void *data, dGeomID geom1, dGeomID geom2);

		dWorldID id;
		ODEReal linearDampening;
		ODEReal angularDampening;
		ODEReal stepTime;
		ODEJointGroup contacts;
		int maxContacts;
		ODESpace space;
		createContactDelegate createContact;
		bool applyDampening;

		void Init(const ODEVector3 &gravity);
		void collide(dGeomID geom1, dGeomID geom2);
		double elapsedTime() const;
		void dampening(dSpaceID space);
	};
}

#endif