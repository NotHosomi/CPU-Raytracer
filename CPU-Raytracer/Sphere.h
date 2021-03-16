#pragma once
#include "Eigen.h"
#include "Colour.h"
#include "Primitive.h"


class Sphere : public Primitive
{
public:
	Sphere(Vec3 position, float radius);
	bool intersect(Ray r, Hit& hit_point) override;

	//Colour col() { return colour;  }

	Vec3 o() { return origin; }
	float r() { return radius; }
private:
	float radius;
	//Colour colour;
};

