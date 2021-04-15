#include "Eigen.h"

Vec3 Vec::newVec3(float x, float y, float z)
{
	Vec3 temp;
	temp << x, y, z;
	return temp;
}

Vec3 Vec::min(Vec3 a, Vec3 b)
{
    // not using for loop to interate thru vector coeffs, cuz why spend an extra tick incrementing the iterator :^)
    if (a.x() < b.x())
        b.x() = a.x();
    if (a.y() < b.y())
        b.y() = a.y();
    if (a.z() < b.z())
        b.z() = a.z();
    return b;
}

Vec3 Vec::max(Vec3 a, Vec3 b)
{
    if (a.x() > b.x())
        b.x() = a.x();
    if (a.y() > b.y())
        b.y() = a.y();
    if (a.z() > b.z())
        b.z() = a.z();
    return b;
}
