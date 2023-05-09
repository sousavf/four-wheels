#ifndef Object_h
#define Object_h

#include <ode/ode.h>
#include <vector>
#include "Auxiliary.h"
#include "Geometry.h"

class World;

class Object
{
	friend class World;
	friend class Space;

	public:
		Object();
		Object(World &world, double mass);
		Object(World &world, double mass, XYZ position, XYZ rotation);
		virtual ~Object();

		bool GetBounce();
		void SetBounce(bool boolean);
		void Right(Intensity force);
		void Left(Intensity force);
		void Front(Intensity force);
		void Back(Intensity force);
		void Up(Intensity force);
		void Down(Intensity force);
		void ApplyForce(double x, double y, double z);
		void ApplyTorque(double x, double y, double z);
		double GetMass();
		::Geometry * Geometry() const;
		virtual void Reset();
		virtual bool WasTouched() const;
		virtual bool Touched(Object& object) const;
		virtual bool Touched(::Geometry& geometry) const;
		dBodyID ID();
		virtual void SetEnable(bool value);
		bool GetEnable() const;

	protected:
		::Geometry *geometry;
		dBodyID body;
		double mass;
		bool bounce;

		void Init(World &world, double mass, XYZ position, XYZ rotation);
		void Init(World &world, double mass);
		virtual void Prepare();
};

#endif