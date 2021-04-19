#include "Ray.h"
#include <assert.h>
#include <cmath>
#include "BVHNode.h"
#include <iostream>

Ray::Ray(Vec3 origin, Vec3 dir) :
	origin(origin),	dir(dir)
{}
#if false
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
	Hit hit;
	//if (demo.intersect(*this, hit_point))
	if (demo.intersect(*this, hit))
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

		return genColFromNormal(hit.normal);
	}
	return Colour(0, 0, 0.3);
}

Colour Ray::cast(std::vector<Primitive*>* demo, int depth)
{
	for (auto prim : *demo)
	{
		Hit hit;
		//if (demo.intersect(*this, hit_point))
		if (prim->intersect(*this, hit))
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

			return genColFromNormal(hit.normal);
		}
		// not Z sorted!
		return Colour(0, 0, 0.3);
	}
}
#endif

//  UNUSED IN FAVOUR OF BVHNode.search()
#if false
Colour Ray::cast(const BVHNode& tree, int depth)
{
	Hit* hit = nullptr;
	//if (demo.intersect(*this, hit_point))
	if (tree.search(*this, hit))
	{
		int x = 1;
#if 0
		Colour netCol;
		if (++depth <= MAX_BOUNCES)
		{

			if (hit.surf_colour.a < 1 && hit.surf_colour.a > 0)
			{
				Ray refracted = Ray(*this);
				if (refracted.refract(hit.normal, ray_medium_index, hit.medium_index))
				{
					netCol = (1 - hit.surf_colour.a) * refracted.cast(tree, depth);
					+= hit.surf_colour.a * reflect(hit.normal);
					netCol
				}
			}
			else if (hit.surf_colour.a = 0)
			{
				if (refract(hit.normal, ray_medium_index, hit.medium_index))
				{
					origin = hit.position;

					netCol = cast(tree, depth);
					+= hit.surf_colour.a * reflect(hit.normal);
					netCol
				}
			}
			reflect(hit.normal);
			origin = hit.position;
			return (1 - reflectivity) * cast(tree, depth) * getLight(hit)
		}
#else
		if (hit)
		{
			return genColFromNormal(hit->normal);
		}
		else
		{
			std::cout << "Something has gone wrong here" << std::endl;
		}
#endif
	}
	return Colour(0, 0, 0.3);
}
#endif

void Ray::reflect(Vec3 normal)
{
	if (normal.norm() != 1)
		normal.normalize();

	// r = -(d.n^)n^ + d - (d.n^)n^
	// let reflected magnitude = incidence magnitude
	dir = dir - 2 * dir.dot(normal) * normal;
}

bool Ray::refract(Vec3 normal, float old_index, float new_index)
{
	if (normal.norm() != 1)
		normal.normalize();

	float index = old_index / new_index;
	float incident_cos = dir.dot(normal);
	float result_sin2 = index * index * (1 - incident_cos * incident_cos);
	if (result_sin2 > 1) // Total Internal Reflection
	{
		return false;
	}
	float result_cos = std::sqrt(1 - result_sin2);
	dir = dir * index + (index * incident_cos - result_cos) * normal;
	return true;
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


///
/// 
/// 
/// 
/// TODO:
/// FIND THE CIRCULAR INCLUDE! 
/// 
/// 
/// 
/// 
/// 