#pragma once
#include "Eigen.h"
#include "Colour.h"
#include "Primitive.h"
#include "Sphere.h"
#include "BVHNode.h"

class Ray
{
public:
	Ray(Vec3 origin, Vec3 dir);
	Colour cast(Primitive& demo, int depth);
	Colour cast(Sphere& demo, int depth);
	Colour cast(BVHNode tree, int depth);

	static constexpr int NUM_BOUNCES = 1;

	Vec3 o() { return origin; }
	Vec3 d() { return dir;  }
	Vec3 at(float t) { return origin + t * dir; }
private:
	void reflect(Vec3 normal);
	void refract(Vec3 normal, float old_index, float new_index);
	Vec3 dir;
	Vec3 origin;


	Vec3 getSphereCollNormal(Vec3 prim_origin, Vec3 hit);
	Vec3 getCubeCollNormal(Vec3 prim_origin, Vec3 hit);
	Colour genColFromNormal(Vec3 normal);
};

