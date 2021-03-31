#pragma once
#include "Eigen.h"
#include <vector>
#include "Colour.h"
#include "BVHNode.h"

class Camera
{
public:
	Camera(int x_res, int y_res, float fov);

	void Capture(const BVHNode& geometry, std::string filename);
	//std::vector<Colour> Capture();
	static constexpr float DRAW_DIST = 1000;
private:
	Colour fireRay(const BVHNode& root, Vec3 dir);

	int _x;
	int _y;
	double pix_ang;

	Vec3 origin = { 0, 0, 0 };
	//Quat angles;
	Vec3 look_dir = { 1, 0, 0 };

	std::vector<Primitive*>* geometry = nullptr;



	Colour genColFromNormal(Vec3 normal);
};

