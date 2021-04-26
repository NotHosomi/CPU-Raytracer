#include "Primitive.h"
#include "Ray.h"

Primitive::Primitive(Vec3 origin, Vec3 min_extents, Vec3 max_extents, Colour col) :
	origin(origin),
	bbox(origin + min_extents, origin + max_extents),
	colour(col)
{}

BBox Primitive::getBBox()
{
	return bbox;
}



bool Primitive::validateHit(const Vec3& pos, Ray r, Hit& hit)
{
	if (!hit.isInitialized())
	{
		hit.init();
		hit.position = pos;
		findNormal(hit);
		hit.surf_colour = colour;
		return true;
	}
	if (hit.compareDist(r.o(), pos))
	{
		hit.position = pos;
		findNormal(hit);
		hit.surf_colour = colour;
		return true;
	}
	return false;
}