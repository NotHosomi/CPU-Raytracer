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

#if 1
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

	if (intersection(r.o().x() - mins.x(), r.at(1000).x() - mins.x(), r, hit) && validateHit(hit, 'x'))
		return true;
	if (intersection(r.o().y() - mins.y(), r.at(1000).y() - mins.y(), r, hit) && validateHit(hit, 'y'))
		return true;
	if (intersection(r.o().z() - mins.z(), r.at(1000).z() - mins.z(), r, hit) && validateHit(hit, 'z'))
		return true;
	if (intersection(r.o().x() - (mins.x() + extents.x()), r.at(1000).x() - (mins.x() + extents.x()), r, hit) && validateHit(hit, 'x'))
		return true;
	if (intersection(r.o().y() - (mins.y() + extents.y()), r.at(1000).y() - (mins.y() + extents.y()), r, hit) && validateHit(hit, 'y'))
		return true;
	if (intersection(r.o().z() - (mins.z() + extents.z()), r.at(1000).z() - (mins.z() + extents.z()), r, hit) && validateHit(hit, 'z'))
		return true;

	return false;
}

float BBox::surfaceArea() const
{
	return 2 * extents.x() * extents.y() + 2 * extents.y() * extents.z() + 2 * extents.x() * extents.z();
}

bool BBox::intersection(float d1, float d2, Ray r, Vec3& hit) const
{
	if ((d1 * d2) >= 0.0f)
		return false;
	if (d1 == d2)
		return false;
	hit = r.at(1000 * (-d1 / (d2 - d1)));
	return true;
}

bool BBox::validateHit(Vec3 hit, char plane) const
{
	switch (plane)
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
#else
// TODO REFACTOR THIS
bool BBox::intersect(Ray r, Vec3& hit) const
{
	//BBox line_bbox(r.o(), r.at(1000));
	//if (!overlaps(line_bbox))
	//	return false;

	float t0 = (mins.x() - r.o().x()) / r.o().x();
	float t1 = (maxs.x() - r.o().x()) / r.o().x();

	if (t0 > t1)
		std::swap(t0, t1);

	// y
	float ty0 = (mins.y() - r.o().y()) / r.d().y();
	float ty1 = (maxs.y() - r.o().y()) / r.d().y();

	if (ty0 > ty1)
		std::swap(ty0, ty1);

	if ((t0 > ty1) || (ty0 > t1))
		return false;

	// order roots
	if (ty0 > t0)
		t0 = ty0;
	if (ty1 < t1)
		t1 = ty1;

	// z
	float tz0 = (mins.z() - r.o().z()) / r.d().z();
	float tz1 = (maxs.z() - r.o().z()) / r.d().z();

	if (tz0 > tz1)
		std::swap(tz0, tz1);

	if ((t0 > tz1) || (tz0 > t1))
		return false;

	if (tz0 > t0)
		t0 = tz0;
	if (tz1 < t1)
		t1 = tz1;

	if (t0 < 0) {
		t0 = t1;
		if (t0 < 0) return false;
	}

	hit = r.at(t0);
	return true;
}
#endif

