#include "Eigen.h"

Vec3 Vec::newVec3(float x, float y, float z)
{
	Vec3 temp;
	temp << x, y, z;
	return temp;
}
