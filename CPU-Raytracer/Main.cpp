
#include <iostream>

#include "Eigen.h"
#include "Camera.h"
#include <vector>
#include "Sphere.h"
#include "Tri.h"
#include "BVHNode.h"


#include <chrono>

int main()
{
    std::chrono::steady_clock::time_point tmr_1 = std::chrono::steady_clock::now();
    std::vector<Primitive*> geometry;

    geometry.emplace_back(new Sphere({ 10, 1.7, 0.6 }, 0.5));
    geometry.emplace_back(new Sphere({ 11, 0.2, -0.6 }, 0.4));
    geometry.emplace_back(new Sphere({ 8, 0.4, -0.6 }, 0.2));
    geometry.emplace_back(new Sphere({ 10, -1.7, 0.6 }, 0.1));
    geometry.emplace_back(new Sphere({ 10, -0.5, 0.4 }, 0.4));
    geometry.emplace_back(new Sphere({ 8, 0.3, -0.3 }, 0.3));
    geometry.emplace_back(new Sphere({ 15, 3, -0.3 }, 0.1));
    geometry.emplace_back(new Sphere({ 25, -5, -3 }, 2));
    geometry.emplace_back(new Sphere({ 9, -1, 0.5 }, 0.3));
    geometry.emplace_back(new Sphere({ 20, -4, 1 }, 0.3));
    //geometry.emplace_back(new Tri({ 15, -2, 0 }, { 15, -1, 0 }, { 15, -2, -1 }));
    BVHNode tree = BVHNode(geometry);
#ifdef NDEBUG
    Camera cam(1920, 1080, 90);
#else
    Camera cam(800, 450, 90);
#endif
    std::chrono::steady_clock::time_point end_1 = std::chrono::steady_clock::now();

    std::cout << "Running!\n";

    std::chrono::steady_clock::time_point tmr_2 = std::chrono::steady_clock::now();
    cam.Capture(tree, "test.bmp");
    std::chrono::steady_clock::time_point end_2 = std::chrono::steady_clock::now();
    std::cout << "Complete!\n" << std::endl;

    std::cout << "Init time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end_1 - tmr_1).count() / 1000.0 << " microseconds" << std::endl;
    //std::cout << "Calc time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end_2 - tmr_2).count() / 1000.0 << " microseconds" << std::endl;
    std::cout << "Calc time: " << std::chrono::duration_cast<std::chrono::microseconds>(end_2 - tmr_2).count() << " microseconds" << std::endl;
}
