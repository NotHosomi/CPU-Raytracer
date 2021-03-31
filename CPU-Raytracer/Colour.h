#pragma once

struct Colour
{
	Colour() = default;
	Colour(double r, double g, double b) :
		r(r), g(g), b(b) {}
	Colour(double r, double g, double b, double a) :
		r(r), g(g), b(b), a(a) {}
	double r = 1;
	double g = 1;
	double b = 1;
	double a = 1;


	Colour& operator*=(float rhs)
	{
		r *= rhs;
		g *= rhs;
		b *= rhs;
		return *this;
	}
	Colour operator+(const Colour& rhs)
	{
		Colour out;
		out.r = r + rhs.r;
		out.g = g + rhs.g;
		out.b = b + rhs.b;
		out.a = a + rhs.a; // Should alpha be ignored here?
		return out;
	}
};