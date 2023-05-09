#ifndef SphereGeometry_h
#define SphereGeometry_h

#include "Geometry.h"
#include "Space.h"

class SphereGeometry : public Geometry
{
	public:
		SphereGeometry(const Space &space, double radius);
		SphereGeometry(const Space &space, double radius, Color color);
		~SphereGeometry();

		virtual void Draw();
		double Width();
		double Height();
		double Length();

	protected:
		double radius;

		void Init(const Space &space, double radius, Color color);
};

#endif