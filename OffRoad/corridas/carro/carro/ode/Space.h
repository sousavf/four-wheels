#ifndef Space_h
#define Space_h

#include <ode/ode.h>
#include <vector>
#include "Object.h"

class Space
{
	friend class World;
	friend class Track;

	public:
		Space();
		Space(Space &other_space);
		~Space();

		void AddObject(Object& object);
		void AddGeometry(Geometry& geometry);
		void Reset();
		void GetObjects(std::vector< Object * >& objects);
		void GetGeometries(std::vector< Geometry * >& geometries);
		void Draw();
		Object * GetObject(dGeomID geometry);
		Geometry * GetGeometry(dGeomID geometry);
		dSpaceID ID() const;
		bool Intersects(Geometry& geometry);
		bool RemoveObject(Object* object);
		bool RemoveGeometry(Geometry* geometry);

	protected:
		std::vector< Object * > objects;
		std::vector< Geometry * > geometries;
		dSpaceID space;

		void Prepare();
};

#endif