#ifndef Geometry_h
#define Geometry_h

#include <ode/ode.h>
#include <vector>
#include "Auxiliary.h"

class Object;

class Geometry
{
	friend class Space;
	friend class Car;
	friend class Object;
	friend class World;

	public:
		enum Color
		{
			White,
			Gray,
			Black,
			Red,
			Blue,
			Green
		};

		enum Transparency
		{
			Transparent,
			AlmostTransparent,
			SemiTransparent,
			AlmostOpaque,
			Opaque
		};

		Geometry();
		virtual ~Geometry();

		virtual XYZ GetPosition();
		virtual XYZ GetRotation();
		XYZ GetPreviousPosition();
		Color GetColor();
		Transparency GetTransparency();
		void SetStartPosition(XYZ position);
		void SetStartRotation(XYZ rotation);

		virtual void SetPosition(XYZ position);
		virtual void SetRotation(XYZ rotation);
		void SetColor(Color color);
		void SetTransparency(Transparency transparency);
		void SetCategory(long bits);
		void SetCollide(long bits);

		dGeomID ID();
		virtual bool Intersects(Geometry &anotherGeometry);
		void RemoveFromSpace();

		virtual void Draw() = 0;
		virtual double Width() = 0;
		virtual double Height() = 0;
		virtual double Length() = 0;
		virtual void Reset();
		virtual bool WasTouched() const;
		virtual bool Touched(Object& object) const;
		virtual bool Touched(Geometry& geometry) const;

		static void GetColors(float *rgb, Color color);

	protected:
		static const Color DEFAULT_COLOR = Gray;

		dGeomID geometry;
		Color color;
		XYZ startPosition;
		XYZ startRotation;
		Color startColor;
		bool firstTime[3];
		XYZ previousPosition;
		Transparency transparency;
		bool touched;
		std::vector< dGeomID > touchedGeometries;

		bool Touched(dGeomID geom) const;
		void GetColors(float *colors);
		float Alpha();
		void AddTouchedGeometry(dGeomID geom);
		void ClearTouchedGeometries();
		virtual void Prepare();
};

#endif