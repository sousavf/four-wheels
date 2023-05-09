#ifndef Auxiliary_h
#define Auxiliary_h

#include <stdlib.h>
#include <math.h>
#include <sstream>

typedef struct XYZ
{
	double x;
	double y;
	double z;

	XYZ()
	{
		SetXYZ(0, 0, 0);
	}

	XYZ(double x, double y, double z)
	{
		SetXYZ(x, y, z);
	}

	void SetXYZ(double x, double y, double z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void SetXYZ(XYZ xyz)
	{
		SetXYZ(xyz.x, xyz.y, xyz.z);
	}

	void Add(XYZ xyz)
	{
		this->x += xyz.x;
		this->y += xyz.y;
		this->z += xyz.z;
	}

	void Subtract(XYZ xyz)
	{
		this->x -= xyz.x;
		this->y -= xyz.y;
		this->z -= xyz.z;
	}

	double DistanceTo(XYZ otherXYZ)
	{
		return sqrt( (this->x - otherXYZ.x) * (this->x - otherXYZ.x)
					+ (this->y - otherXYZ.y) * (this->y - otherXYZ.y)
					+ (this->z - otherXYZ.z) * (this->z - otherXYZ.z) );
	}

	double XYDistanceTo(XYZ otherXYZ)
	{
		return sqrt( (this->x - otherXYZ.x) * (this->x - otherXYZ.x)
					+ (this->y - otherXYZ.y) * (this->y - otherXYZ.y) );
	}

	friend std::ostream& operator << (std::ostream &os, XYZ &xyz)
	{
		os << "(" << xyz.x << "," << xyz.y << "," << xyz.z << ")";

		return os;
	}

	friend std::istream& operator >> (std::istream &is, XYZ &xyz)
	{
		double x, y, z;
		char c;

		is >> c >> x >> c >> y >> c >> z >> c;
		xyz.SetXYZ(x, y, z);

		return is;
	}
} XYZ;



/*
bool operator == (const XYZ &xyz1, const XYZ &xyz2)
{
	return (xyz1.x == xyz2.x) && (xyz1.y == xyz2.y) && (xyz1.z == xyz2.z);
}
*/



enum Intensity
{
	Minimum = 5,
	Medium = 10,
	Maximum = 15
};



/// Converte um tipo de dados em string.
template<typename T> 
std::string ToString(T d) { 
  std::stringstream t; 
  
  t << d; 

  return t.str(); 
}

/// alias
template<typename T> 
std::string String(T d) { 
  return ToString(d);
}

#endif
