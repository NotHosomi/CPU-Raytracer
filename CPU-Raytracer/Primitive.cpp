#include "Primitive.h"

Primitive::Primitive(Vec3 origin, Vec3 min_extents, Vec3 max_extents) :
	origin(origin),
	bbox(origin + min_extents, origin + max_extents)
{}

BBox Primitive::getBBox()
{
	return bbox;
}
