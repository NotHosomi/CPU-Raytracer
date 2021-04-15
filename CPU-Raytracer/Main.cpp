
#include <iostream>

#include "Eigen.h"
#include "Camera.h"
#include <vector>
#include "Sphere.h"
#include "Tri.h"
#include "BVHNode.h"

int main()
{
    std::vector<Primitive*> geometry;

    //geometry.emplace_back(new Sphere({ 10, 1.7, 0.6 }, 0.5));
    //geometry.emplace_back(new Sphere({ 11, 0.2, -0.6 }, 0.4));
    //geometry.emplace_back(new Sphere({ 8, 0.2, -0.6 }, 0.2));
    geometry.emplace_back(new Tri({ 15, -1, 0 }, { 15, 1, 0 }, { 15, 1, -1 }));
    BVHNode tree = BVHNode(geometry);

    Camera cam(800, 450, 90);

    std::cout << "Running!\n";
    cam.Capture(tree, "test.bmp");
    std::cout << "Complete!" << std::endl;
}
