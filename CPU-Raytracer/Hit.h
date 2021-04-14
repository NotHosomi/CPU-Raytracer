#pragma once
#include "Eigen.h"
#include "Colour.h"

struct Hit
{
	bool compareDist(Vec3 ray_origin, Vec3 new_pos)
	{
		float d1 = (position - ray_origin).norm();
		float d2 = (new_pos - ray_origin).norm();
		return d2 < d1;
	}
	// hit 
	Vec3 position = { 1024, 1024, 1024 };
	Vec3 normal = { 0, 0, 0 };
	Colour surf_colour = Colour(0, 0, 0.2);

	bool isInitialized() { return initialized; }
	void init() { initialized = true; }
private:
	// not using std::optional as it would reduce access speed
	bool initialized = false;
};