#pragma once

#include <Eigen/Dense>
#include <Eigen/Geometry>
using namespace Eigen;
using Vec3 = Vector3f;
using Quat = Quaternionf;

namespace Vec
{
	Vec3 newVec3(float x, float y, float z);
}