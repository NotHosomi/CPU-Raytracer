#include "Camera.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "bitmap_format.h"
#include "Ray.h"

#include "Sphere.h"

Camera::Camera(int x_res, int y_res, float fov)
{
	_x = x_res;
	_y = y_res;
	//pix_ang = (fov / x_res) * M_PI / 180.0;
}

void Camera::Capture(const BVHNode& geometry, std::string filename)
{
	BMP::BMP img(_x, _y, false);

#if 0
	// Rotation data
	Quat x_step;
	x_step = AngleAxis<float>(pix_ang, Vec3::UnitZ());
	Quat y_step;
	y_step = AngleAxis<float>(pix_ang, Vec3::UnitY());
	Quat sl_startang;
	sl_startang = AngleAxis<float>(-pix_ang * (_y / 2.0), Vec3::UnitY())
		* AngleAxis<float>(-pix_ang * (_x / 2.0), Vec3::UnitZ());
	Vec3 scanline_start_ray = sl_startang * look_dir;
	
	for (int i = 0; i < _y; ++i)
	{
		Vec3 ray_dir = scanline_start_ray;
		for (int j = 0; j < _x; ++j)
		{
			Colour pxl = fireRay(ray_dir);
			img.set_pixel(j, i, (uint8_t)(pxl.r * 255), (uint8_t)(pxl.g * 255), (uint8_t)(pxl.b * 255), 0);
			ray_dir = x_step * ray_dir;
		}
		scanline_start_ray = y_step * scanline_start_ray;
	}
#else
	float step = 1.0f / (_x / 0.5f);
	Vec3 ray_dir = look_dir;
	for (int i = -_y / 2.0; i < _y / 2.0; ++i)
	{
		//std::cout << "x: " << i << std::endl;
		ray_dir.z() = i * step;
		for (int j = -_x / 2.0; j < _x / 2.0; ++j)
		{
			ray_dir.y() = j * step;
			//std::cout << "x:\t" << i << ",\ty:\t" << j << std::endl;
			Colour pxl = fireRay(origin, geometry, ray_dir.normalized());
			img.set_pixel(j + _x / 2.0, i + _y / 2.0, (uint8_t)(pxl.r * 255), (uint8_t)(pxl.g * 255), (uint8_t)(pxl.b * 255), 0);
		}
	}
#endif


	img.write(filename.c_str());
}



Colour Camera::fireRay(Vec3 source, const BVHNode& root, Vec3 dir)
{
	Ray r(source, dir * DRAW_DIST);
	Hit hit;
	bool search_res = root.search(r, hit);

	if(hit.isInitialized())
	{
		//return genColFromNormal(hit.normal); // (Colour of light * surface reflectance * dot(normal, dir to light)) / dist to light source squared
		return (hit.surf_colour / M_PI) * light_ambient_col;
	}
	return Colour(0, 0, 0);
}

Colour Camera::genColFromNormal(Vec3 normal)
{
	normal = normal.cwiseAbs();
	return Colour(normal.x(), normal.y(), normal.z());
}