#ifndef SoccerField_h
#define SoccerField_h

#include "Auxiliary.h"
#include "Space.h"
#include "BoxGeometry.h"

class SoccerField
{
	public:
		SoccerField(World &world);
		SoccerField(World &world, XYZ position);
		SoccerField(World &world, double multiplier);
		SoccerField(World &world, double multiplier, XYZ position);
		SoccerField(World &world, double width, double length, double netLength);
		SoccerField(World &world, double width, double length, double netLength, XYZ position);
		SoccerField(World &world, double width, double length, double netLength, double divWidth
				, double divHeight);
		SoccerField(World &world, double width, double length, double netLength, double divWidth
				, double divHeight, XYZ position);
		~SoccerField();

		double GetWidth() const;
		double GetLength() const;
		double GetNetLength() const;
		double GetDivWidth() const;
		double GetDivHeight() const;
		Space* GetSpace() const;
		void SetCategory(long bits);
		void SetCollide(long bits);
		bool Net1WasTouched() const;
		bool Net2WasTouched() const;
		bool Net1Touched(Object& object) const;
		bool Net1Touched(Geometry& geometry) const;
		bool Net2Touched(Object& object) const;
		bool Net2Touched(Geometry& geometry) const;
		void IncNet1Score();
		void IncNet2Score();
		int Net1Score() const;
		int Net2Score() const;
		BoxGeometry* GetNet1() const;
		BoxGeometry* GetNet2() const;
		XYZ& GetPosition();

	private:
		double width;
		double length;
		double divWidth;
		double divHeight;
		double netLength;
		Space* space;
		BoxGeometry** geometries;
		int score[2];
		XYZ position;

		static const int NET1 = 0;
		static const int NET2 = 1;
		static const int SIDE1 = 2;
		static const int SIDE2 = 3;
		static const int N_GEOMS = 8;

		void Init(World &world, double width, double length, double netLength, double divWidth
				, double divHeight, XYZ position);
};

#endif