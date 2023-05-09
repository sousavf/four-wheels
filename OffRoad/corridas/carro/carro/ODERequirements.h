#ifndef ODEREQUIREMENTS_H
#define ODEREQUIREMENTS_H

#include <ode/ode.h>
#include <assert.h>

typedef dReal ODEReal;
#define ODEInfinity dInfinity;

namespace ODE
{
	enum ODEDirection;
	class ODEVector2;
	class ODEVector3;
	class ODEVector4;
	class ODEQuaternion;
	class ODEMatrix3;
	class ODEContact;
	class ODEContactDefinition;
	class ODEJoint;
	class ODEFixedJoint;
	class ODESliderJoint;
	class ODEHinge2Joint;
	class ODEJointGroup;
	class ODEGeometry;
	class ODEBoxGeometry;
	class ODESphereGeometry;
	class ODECylinderGeometry;
	class ODEPlaneGeometry;
	class ODEMass;
	class ODEBoxMass;
	class ODESphereMass;
	class ODECylinderMass;
	class ODEBody;
	class ODEObject;
	class ODESimpleObject;
	class ODEComplexObject;
	class ODEBox;
	class ODESphere;
	class ODECylinder;
	class ODEWheel;
	class ODECar;
	class ODESpace;
	class ODEWorld;
	class ODESimulation;
	class ODECarDefinition;
	class ODECarControl;
	class ODETrackSegmentDefinition;
	class ODETrackSegment;
	class ODETrack;
	class ODETrackValidator;
}

#endif