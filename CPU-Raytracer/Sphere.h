#pragma once
#include "Eigen.h"
#include "Colour.h"
#include "Primitive.h"


class Sphere : public Primitive
{
public:
	Sphere(Vec3 position, float radius);
	bool intersect(Ray r, Hit& hit) override;
	bool validateHit(const Vec3& pos, Ray r, Hit& hit);

	float r() { return radius; }
private:
	float radius;
};

