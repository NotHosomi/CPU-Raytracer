#pragma once
#include "Eigen.h"

class Ray;

class BBox
{
public:
	BBox() = default;
	BBox(Vec3 mins, Vec3 maxs);
	BBox(Vec3 center, float width, float height, float depth);

	Vec3 center() const;
	Vec3 getMins() const;
	Vec3 getExtents() const;
	Vec3 getMax() const;

	bool overlaps(Vec3 point) const;
	bool overlaps(BBox other) const;
	bool intersect(Ray r, Vec3& point) const;
	float surfaceArea() const;

private:
	bool between(float value, float min, float max) const;
	bool intersection(float d1, float d2, Ray r, Vec3& hit, char axis) const;
	Vec3 mins = { 0, 0, 0 };
	Vec3 extents = { 0, 0, 0 };
	Vec3 maxs = { 0, 0, 0 };
};

