#pragma once
#include "Eigen.h"

class Line
{
public:
	Line(Vec3 start, Vec3 end);
	Line(Vec3 start, Vec3 dir, float length);


	Vec3 start();
	Vec3 offset();
	float dist();
	Vec3 dir();
	Vec3 end();

	void start(const Vec3& v);
	void offset(const Vec3& v);
	void dir(const Vec3& d);
	void dist(float d);
	void scale(float d);
	void end(const Vec3& v);

	bool doesIntersect(Line other);

private:
	Vec3 _start;
	Vec3 _offset;
};

