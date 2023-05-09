#ifndef Line_h
#define Line_h

#include "Geometry.h"

class Line
{
	public:
		struct Point
		{
			protected:
				double x;
				double y;

			public:
				Point()
				{
					this->x = 0;
					this->y = 0;
				}

				Point(double x, double y)
				{
					this->x = x;
					this->y = y;
				}

				double GetX()
				{
					return this->x;
				}

				double GetY()
				{
					return this->y;
				}

				void SetX(double value)
				{
					this->x = value;
				}

				void SetY(double value)
				{
					this->y = value;
				}

				void SetXY(double x, double y)
				{
					this->x = x;
					this->y = y;
				}
		};

		Line();
		Line(Line &anotherLine);
		Line(double x1, double y1, double x2, double y2);
		Line(Point p1, Point p2);
		~Line();

		Point GetP1();
		Point GetP2();
		void SetP1(Point p1);
		void SetP2(Point p2);
        double GetM();
		double GetB();
		bool Intersects(Point point);
		bool Intersects(Line &anotherLine);
		static void Draw(XYZ p1, XYZ p2, Geometry::Color color);

	protected:
		Point p1;
		Point p2;
		double m;
		double b;

		void SetMB();
		void Init(Point p1, Point p2);
};

#endif