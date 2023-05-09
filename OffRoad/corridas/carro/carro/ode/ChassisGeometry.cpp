#include "ChassisGeometry.h"

/// Constr�i uma nova geometria de chassis.
ChassisGeometry::ChassisGeometry(const Space &space, double width, double height, double length, Color color)
						:BoxGeometry(space, width, height, length, color)
{
}



/// Destr�i a geometria.
ChassisGeometry::~ChassisGeometry()
{
}