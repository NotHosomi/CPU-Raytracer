#pragma once
#include "Eigen.h"
#include "Colour.h"

struct Hit
{
	Vec3 position;
	Vec3 normal;
	Colour surf_colour;
};