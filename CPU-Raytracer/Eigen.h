#pragma once

#include <Eigen/Dense>
#include <Eigen/Geometry>
using namespace Eigen;
using Vec3 = Vector3f;
using Quat = Quaternionf;

namespace Vec
{
	Vec3 newVec3(float x, float y, float z);

	// should these be const refs? Vec3 size is 12 bytes, ref size is 8 bytes
	Vec3 min(Vec3 a, Vec3 b);
	Vec3 max(Vec3 a, Vec3 b);
}