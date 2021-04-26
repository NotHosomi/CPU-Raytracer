#pragma once
#include "Eigen.h"
#include "Colour.h"
#include "Primitive.h"


class Sphere : public Primitive
{
public:
	Sphere(Vec3 position, float radius, Colour col);
	bool intersect(Ray r, Hit& hit) override;

	float r() { return radius; }
private:
	void findNormal(Hit& hit) override;
	float radius;
};

