#pragma once
#include "Eigen.h"
#include "Colour.h"

struct Light
{
	Vec3 position = { 0, 0, 0 };
	Colour colour = { 0, 0, 0 };
	float brightness = 1;
};