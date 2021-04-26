#pragma once
#include "Eigen.h"
#include "BBox.h"
#include "Hit.h"

class ray;

class Primitive
{
public:
	Primitive(Vec3 origin, Vec3 mins, Vec3 maxs, Colour col);
	BBox getBBox();
	virtual bool intersect(Ray r, Hit& hit) = 0;
	Colour col() { return colour; }
	Vec3 o() { return origin; }
protected:
	bool validateHit(const Vec3& pos, Ray r, Hit& hit);
	virtual void findNormal(Hit& hit) = 0;
	Vec3 origin;
	BBox bbox;
	Colour colour; // TODO: set this
};

