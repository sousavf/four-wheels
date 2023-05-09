#include "ChassisGeometry.h"

/// Constrói uma nova geometria de chassis.
ChassisGeometry::ChassisGeometry(const Space &space, double width, double height, double length, Color color)
						:BoxGeometry(space, width, height, length, color)
{
}



/// Destrói a geometria.
ChassisGeometry::~ChassisGeometry()
{
}