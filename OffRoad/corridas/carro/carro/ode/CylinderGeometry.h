#ifndef CylinderGeometry_h
#define CylinderGeometry_h

#include "Geometry.h"
#include "Space.h"

class CylinderGeometry : public Geometry
{
	public:
		CylinderGeometry(const Space &space, double radius, double length);
		CylinderGeometry(const Space &space, double radius, double length, Color color);
		~CylinderGeometry();

		virtual void Draw();
		double Width();
		double Height();
		double Length();

	protected:
		double radius;
		double length;

		void Init(const Space &space, double radius, double length, Color color);
};

#endif