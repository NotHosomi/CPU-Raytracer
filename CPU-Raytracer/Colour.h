#pragma once

struct Colour
{
	Colour();
	Colour(double r, double g, double b) :
		r(r), g(g), b(b) {}
	Colour(double r, double g, double b, double a) :
		r(r), g(g), b(b), a(a) {}
	double r = 1;
	double g = 1;
	double b = 1;
	double a = 1;
};