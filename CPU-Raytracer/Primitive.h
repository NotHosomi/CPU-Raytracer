#pragma once
#include "Eigen.h"
#include "BBox.h"
#include "Hit.h"

class ray;

class Primitive
{
public:
	Primitive(Vec3 origin, Vec3 mins, Vec3 maxs);
	BBox getBBox();
	virtual bool intersect(Ray r, Hit& hit_point);
protected:
	Vec3 origin;
	BBox bbox;
};

