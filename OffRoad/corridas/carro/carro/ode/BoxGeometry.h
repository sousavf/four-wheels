#ifndef BoxGeometry_h
#define BoxGeometry_h

#include "Geometry.h"
#include "Space.h"

class BoxGeometry : public Geometry
{
	friend class SoccerField;

	public:
		BoxGeometry();
		BoxGeometry(const Space &space, double size);
		BoxGeometry(const Space &space, double size, Color color);
		BoxGeometry(const Space &space, double width, double height, double length);
		BoxGeometry(const Space &space, double width, double height, double length, Color color);
		~BoxGeometry();

		void Draw();
		double Width();
		double Height();
		double Length();

	protected:
		double width;
		double height;
		double length;

		void Init(const Space &space, double width, double height, double length, Color color);
};

#endif