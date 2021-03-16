#include "Ray.h"
#include <assert.h>
#include <cmath>

Ray::Ray(Vec3 origin, Vec3 dir) :
	origin(origin),	dir(dir)
{}

Colour Ray::cast(Primitive& demo, int depth)
{
	Vec3 hit_point;
	//if (demo.intersect(*this, hit_point))
	if (demo.getBBox().intersect(*this, hit_point))
	{
		int x = 1;
		/*
		if(++depth <= MAX_DEPTH)
		{
			if(surface.transparent())
			{
				refract()
			}
			else
			{
				reflect(surface.normal)
			}
			cast(BVH, depth)
		}
		*/
		return genColFromNormal(getCubeCollNormal(demo.getBBox().center(), hit_point));
	}
	return Colour(0, 0, 0.3);
}
Colour Ray::cast(Sphere& demo, int depth)
{
	Vec3 hit_point;
	//if (demo.intersect(*this, hit_point))
	if (demo.intersect(*this, hit_point))
	{
		int x = 1;
		/*
		if(++depth <= MAX_DEPTH)
		{
			if(surface.transparent())
			{
				refract()
			}
			else
			{
				reflect(surface.normal)
			}
			cast(BVH, depth)
		}
		*/

		return genColFromNormal(getSphereCollNormal(demo.o(), hit_point));
	}
	return Colour(0, 0, 0.3);
}

Colour Ray::cast(BVHNode tree, int depth)
{
	Hit hit;
	if (tree.search(*this, hit))
	{

	}
	return Colour(0, 0, 0.3);
}


void Ray::reflect(Vec3 normal)
{
	if (normal.norm() != 1)
		normal.normalize();

	// r = -(d.n^)n^ + d - (d.n^)n^
	// let reflected magnitude = incidence magnitude
	dir = dir - 2 * dir.dot(normal) * normal;
}

void Ray::refract(Vec3 normal, float old_index, float new_index)
{
	if (normal.norm() != 1)
		normal.normalize();

	// https://graphics.stanford.edu/courses/cs148-10-summer/docs/2006--degreve--reflection_refraction.pdf
	float n = old_index / new_index;
	float cosI = dir.dot(normal);
	float sinT2 = n * n * (1 - cosI * cosI);
	if (sinT2 > 1) // Total Internal Reflection
	{
		reflect(normal);
		return;
	}
	float cosT = std::sqrt(1 - sinT2);

	
}


Vec3 Ray::getSphereCollNormal(Vec3 prim_origin, Vec3 hit)
{
	return (hit - prim_origin).normalized();
}

Vec3 Ray::getCubeCollNormal(Vec3 prim_origin, Vec3 hit)
{
	Vec3 h = hit - prim_origin;
	h = h.cwiseAbs();
	int largest_coeff = 0;
	if (h[1] > h[largest_coeff])
	{
		largest_coeff = 1;
	}
	if (h[2] > h[largest_coeff])
	{
		largest_coeff = 2;
	}
	Vec3 normal;
	normal.setZero();
	if(h[largest_coeff] > 0)
		normal[largest_coeff] = 1;
	else
		normal[largest_coeff] = -1;

	return normal;
}

Colour Ray::genColFromNormal(Vec3 normal)
{
	normal = normal.cwiseAbs();
	return Colour(normal.x(), normal.y(), normal.z());
}