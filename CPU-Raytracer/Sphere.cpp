#include "Sphere.h"
#include "Ray.h"

Sphere::Sphere(Vec3 position, float radius) :
	Primitive(position,
			Vec::newVec3(-radius, -radius, -radius),
			Vec::newVec3(radius, radius, radius)),
	radius(radius)
{}

bool Sphere::intersect(Ray r, Hit* hit)
{
	// Quadratic formula
	Vec3 L = r.o() - origin;
	float a = r.d().dot(r.d());
	float b = 2.0f * L.dot(r.d());
	float c = L.dot(L) - radius * radius;
	float discriminant = b * b - 4 * a * c;
	// no hit
	if (discriminant < 0)
		return false;
	// tangent
	if (discriminant == 0)
	{
		Vec3 pos = r.at(-0.5f * b / a);

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
		hit.position = r.at(t0);
		hit.normal = (hit.position - origin).normalized();
		hit.surf_colour = colour;
		return true;
	}
	if(t1 > 0)
	{
		hit.position = r.at(t1);
		hit.normal = (hit.position - origin).normalized();
		hit.surf_colour = colour;
		return true;
	}
	return false;
}

bool Sphere::validateHit(const Vec3& pos, Ray r, Hit* hit)
{
	if (hit == nullptr)
	{
		hit = new Hit(pos,
			(pos - origin).normalized(),
			colour);
	}
	else if (hit->compareDist(r.o(), pos))
	{
		hit->position = pos;
		hit->normal = (pos - origin).normalized();
		hit->surf_colour = colour;
	}
}
