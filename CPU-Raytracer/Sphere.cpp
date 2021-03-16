#include "Sphere.h"
#include "Ray.h"

Sphere::Sphere(Vec3 position, float radius) :
	Primitive(position, { -radius, -radius, -radius }, { radius, radius, radius }),
	radius(radius)
{}

bool Sphere::intersect(Ray r, Hit& hit_point) override
{
	// Quadratic formula
	Vec3 L = r.o() - origin;
	float a = r.d().dot(r.d());
	float b = 2.0 * L.dot(r.d());
	float c = L.dot(L) - radius * radius;
	float discriminant = b * b - 4 * a * c;
	// no hit
	if (discriminant < 0)
		return false;
	// tangent
	if (discriminant == 0)
	{
		hit = r.at(-0.5 * b / a);
		return true;
	}
	// double intersect
	float t0;
	float t1;
	// resolve roots
	float q = sqrt(discriminant);
	if (b <= 0)
		q *= -1;
	q = -0.5f * (b + q);
	t0 = q / a;
	t1 = c / q;
	// order intersects for simplicity
	if (t0 > t1)
		std::swap(t0, t1);

	if (t0 > 0)
	{
		hit = r.at(t0);
		return true;
	}
	if(t1 > 0)
	{
		hit = r.at(t1);
		return true;
	}
	return false;
}
