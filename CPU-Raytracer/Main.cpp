
#include <iostream>

#include "Eigen.h"
#include "Camera.h"

int main()
{
    std::cout << "Running!\n";
    Camera cam(800, 450, 90);
    cam.Capture("test.bmp");
    std::cout << "Complete!" << std::endl;
}
