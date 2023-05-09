#ifndef Ray_h
#define Ray_h

#include "World.h"

class Ray : public Geometry
{
	public:
		Ray(double length);
		Ray(Object* object, double length);
		~Ray();

		void Draw();
		double Width();
		double Height();
		double Length();
		void SetRotation(XYZ rotation);
		void Scan(World &world);
		double GetLength();
		void Ignore(Object& object);
		void Ignore(Geometry& geometry);
		void Ignore(Space *space);
		void Attach(Object* object);
		double* GetDistances() const;
		void SetDoScan(bool value);
		bool GetDoScan() const;
		void SetLevelOfScan(int value);
		int GetLevelOfScan();
		void SetDraw(bool value);
		bool GetDraw() const;
		void SetOnlyFront(bool value);
		bool GetOnlyFront() const;
		void ClearIgnored();
		void SetEnable(bool value);
		bool IsEnabled() const;

	protected:
		bool enabled;
		double length;
		Object* object;
		std::vector< dGeomID > ignoredGeometries;
		double* distances;
		bool doScan;
		bool draw;
		int levelOfScan;
		bool onlyFront;

		void Init(double length);
		bool IgnoredGeometry(dGeomID geometry) const;
		std::vector< dGeomID > AcceptedGeomIDs(std::vector< Object * >& objects
										, std::vector< Geometry * >& geometries) const;
		double Collide(std::vector< dGeomID > &geoms) const;
};

#endif