#ifndef World_h
#define World_h

#include <ode/config.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <ode/ode.h>
#include <drawstuff/drawstuff.h>
#include <assert.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Auxiliary.h"
#include "Math.h"
#include "Geometry.h"
#include "Object.h"
#include "Space.h"
#include "BoxGeometry.h"
#include "Box.h"
#include "SphereGeometry.h"
#include "Sphere.h"
#include "Camera.h"
#include "Ray.h"
#include "Joint.h"
#include "FixedJoint.h"
#include "Hinge2Joint.h"
#include "CylinderGeometry.h"
#include "Cylinder.h"
#include "WheelGeometry.h"
#include "Wheel.h"
#include "SliderJoint.h"
#include "SoccerRobot.h"
#include "SoccerField.h"
#include "..\genetic_algorithms\WorldChromossome.h"

class World
{
	friend class Ray;

	public:
		World(double gravity = 9.81);
		~World();

		void SetGravity(double gravity);
		void Start();
		void AddSpace(Space &space);
		void SetInputResolver(void (*command)(int cmd));
		void SetLoopFunction(void (*loop)(int));
		Camera* GetCamera();
		Space* WorldSpace();
		void Reset();
		std::vector< Object * > GetObjects();
		std::vector< Geometry * > GetGeometries();
		void AddRay(Ray *ray);
		bool RemoveRay(Ray *ray);
		dWorldID ID();
		void SetTimeDependent(bool value);
		bool GetTimeDependent();
		void SetDoDampening(bool value);
		bool GetDoDampening();
		void SetDoAerodynamics(bool value);
		bool GetDoAerodynamics();
		void SetAngularDampening(double value);
		double GetAngularDampening();
		void SetLinearDampening(double value);
		double GetLinearDampening();
		void SetAerodynamic(double value);
		double GetAerodynamic();
		bool Started();
		bool RemoveObject(Object* object);
		bool RemoveSpace(Space* space);
		void SetStepSize(double value);
		double GetStepSize() const;
		void SetDraw(bool draw);
		bool GetDraw() const;
		void SetParams(double gravity, double angularDampening, double linearDampening, double aerodynamic
				, double mu, double mu2, double slip1, double slip2, double soft_erp, double soft_cfm);
		void SetParams(WorldChromossome &c);

	protected:
		static World *handler;
		static const double STEP_T;		// o tempo que dura cada passo na simulação (em ms)
		static const double STEP_SIZE;	// o tamanho do step que dá quando a simulação não está dependente do tempo
		static const int CONTACTS = 5;	// o número de contactos temporários que vão ser criados entre 2 objectos numa colisão

		std::vector< Space* > spaces;
		std::vector< Ray* > rays;
		dWorldID world;
		dReal gravity;
		dJointGroupID contacts;
		Camera camera;
		void (*command)(int);
		void (*loop)(int);
		bool started;
		dGeomID ground;
		bool timeDependent;
		bool doDampening;
		bool doAerodynamics;
		double angularDampening;
		double linearDampening;
		double aerodynamic;
		double stepSize;
		bool draw;

		double mu;
		double mu2;
		double slip1;
		double slip2;
		double soft_erp;
		double soft_cfm;

		static void ResetAux();
		static void LoopAux(int pause);
		static void NearCallbackAux(void *data, dGeomID o1, dGeomID o2);

		Geometry * GetGeometry(dGeomID geometry);
		Object * GetObject(dGeomID geometry);
		void Draw();
		void NearCallback(void *data, dGeomID o1, dGeomID o2);
		void Loop(int pause);
		void Prepare();
		std::vector< Object * > GetObjectsExcept(dSpaceID space);
		std::vector< Geometry * > GetGeometriesExcept(dSpaceID space);
		void Step(int pause, double step);
		void Dampening(Object &obj);
		void Aerodynamics(Object &obj);
		void Collide(dGeomID o1, dGeomID o2);
		void CreateContact(dContact *contact, Object *obj1, Object *obj2);
		void RaysScan();
};

#endif