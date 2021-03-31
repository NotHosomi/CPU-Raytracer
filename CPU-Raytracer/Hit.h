#pragma once
#include "Eigen.h"
#include "Colour.h"

struct Hit
{
	Hit(Vec3 pos, Vec3 norm, Colour col) :
		position(pos), normal(norm), surf_colour(col)
	{}
	bool compareDist(Vec3 ray_origin, Vec3 new_pos)
	{
		float d1 = (position - ray_origin).norm();
		float d2 = (new_pos - ray_origin).norm();
		return d2 < d1;
	}
	// hit 
	Vec3 position = { 1024, 1024, 1024 };
	Vec3 normal;
	Colour surf_colour = Colour(0, 0, 0.2);

};