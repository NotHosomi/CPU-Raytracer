#include "Tri.h"
#include "Ray.h"
#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>

Tri::Tri(Vec3 a, Vec3 b, Vec3 c) :
	Primitive((a + b + c)/3,
		Vec::min(a, Vec::min(b, c)),
		Vec::max(a, Vec::max(b, c)))
{
	// store verts
	verts[0] = a;
	verts[1] = b;
	verts[2] = c;

	// precompute normal
	Vec3 edge1 = b - a;
	Vec3 edge3 = c - a;
	normal = edge3.cross(edge1);
	plane_depth = normal.dot(a);

	// precompute edges
	edges[0] = verts[1] - verts[0];
	edges[1] = verts[2] - verts[1];
	edges[2] = verts[0] - verts[2];
}

bool Tri::intersect(Ray r, Hit& hit)
{
	// check ray dir faces plane
	if (normal.dot(r.d()) <= 0)
		return false;
	// ray-plane intersection
	float t = -(r.o().dot(normal) + plane_depth) / r.d().dot(normal);
	Vec3 pos = r.at(t);
	// check intersection point within tri
	for (int i = 0; i < 3; ++i)
	{
		if(normal.dot(edges[i].cross(pos - verts[i])) < 0)
		{
			// pos is outside of the tri
			return false;
		}
		// TODO: WHY DOESNT EITHER OF THESE METHODS WORK?!
	}
	validateHit(pos, r, hit);
	return true;
}

void Tri::findNormal(Hit& hit)
{
	hit.normal = normal;
}
