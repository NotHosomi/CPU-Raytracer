#include "BBox.h"
#include <assert.h>
#include "Ray.h"

BBox::BBox(Vec3 mins, Vec3 maxs)
{
	for (int i = 0; i < 3; ++i)
	{
		float temp;
		if (mins[i] > maxs[i])
		{
			std::swap(mins[i], maxs[i]);
		}
	}
	this->mins = mins;
	this->maxs = maxs;
	extents = maxs - mins;
	
	assert("INVALID BOUNDING BOX VOLUME" && extents.minCoeff() >= 0);
}

BBox::BBox(Vec3 center, float width, float height, float depth)
{
	extents << width, height, depth;
	assert("INVALID BOUNDING BOX VOLUME" && extents.minCoeff() >= 0);

	mins = center - extents * 0.5f;
}

Vec3 BBox::center() const
{
	return mins + 0.5f * extents;
}

Vec3 BBox::getMins() const
{
	return mins;
}

Vec3 BBox::getExtents() const
{
	return extents;
}

Vec3 BBox::getMax() const
{
	return mins + extents;
}

bool BBox::overlaps(Vec3 point) const
{
	return between(point.x(), mins.x(), mins.x() + extents.x())
		&& between(point.y(), mins.y(), mins.y() + extents.y())
		&& between(point.z(), mins.z(), mins.z() + extents.z());
}

bool BBox::overlaps(BBox other) const
{
	bool x = between(mins.x(), other.getMins().x(), other.getMax().x()) ||
		between(other.getMins().x(), mins.x(), mins.x() + extents.x());

	bool y = between(mins.y(), other.getMins().y(), other.getMax().y()) ||
		between(other.getMins().y(), mins.y(), mins.y() + extents.y());

	bool z = between(mins.z(), other.getMins().z(), other.getMax().z()) ||
		between(other.getMins().z(), mins.z(), mins.z() + extents.z());

	return x && y && z;
}

// inclusive bounds check
bool BBox::between(float value, float min, float max) const
{
	return (value >= min) && (value <= max);
}

bool BBox::intersect(Ray r, Vec3& hit) const
{
	// check the line is near this bbox
	BBox line_bbox(r.o(), r.at(1000));
	if (!overlaps(line_bbox))
		return false;

	// if the line starts inside the box, count as hit @ line start
	if (overlaps(r.o()))
	{
		hit = r.o();
		return true;
	}

	if (intersection(r.o().x() - mins.x(), r.at(1000).x() - mins.x(), r, hit, 'x'))
		return true;
	if (intersection(r.o().y() - mins.y(), r.at(1000).y() - mins.y(), r, hit, 'y'))
		return true;
	if (intersection(r.o().z() - mins.z(), r.at(1000).z() - mins.z(), r, hit, 'z'))
		return true;
	if (intersection(r.o().x() - (mins.x() + extents.x()), r.at(1000).x() - (mins.x() + extents.x()), r, hit, 'x'))
		return true;
	if (intersection(r.o().y() - (mins.y() + extents.y()), r.at(1000).y() - (mins.y() + extents.y()), r, hit, 'y'))
		return true;
	if (intersection(r.o().z() - (mins.z() + extents.z()), r.at(1000).z() - (mins.z() + extents.z()), r, hit, 'z'))
		return true;

	return false;
}

float BBox::surfaceArea() const
{
	return 2 * extents.x() * extents.y() + 2 * extents.y() * extents.z() + 2 * extents.x() * extents.z();
}

// d1 is origin from vertex
// d2 is ray_dest from vertex
bool BBox::intersection(float d1, float d2, Ray r, Vec3& hit, char axis) const
{
	// is ray in direction of the plane 
	if ((d1 * d2) >= 0.0f)
		return false;
	// is ray parallel to place
	if (d1 == d2)
		return false;
	// find the ray-plane intersect point
	hit = r.at(1000 * (-d1 / (d2 - d1)));

	// is the point within the face's bounds
	switch (axis)
	{
	case 'x':
		return between(hit.z(), mins.z(), mins.z() + extents.z())
			&& between(hit.y(), mins.y(), mins.y() + extents.y());
	case 'y':
		return between(hit.z(), mins.z(), mins.z() + extents.z())
			&& between(hit.x(), mins.x(), mins.x() + extents.x());
	case 'z':
		return between(hit.x(), mins.x(), mins.x() + extents.x())
			&& between(hit.y(), mins.y(), mins.y() + extents.y());
	}
	return false;
}