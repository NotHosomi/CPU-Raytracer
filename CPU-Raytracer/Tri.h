#pragma once
#include "Primitive.h"
class Tri :
    public Primitive
{
public:
    Tri(Vec3 a, Vec3 b, Vec3 c);
    Vec3 verts[3] = { {0,0,0},{0,0,0},{0,0,0} };
    Vec3 edge_normals[3] = { {0,0,0},{0,0,0},{0,0,0} };
    Vec3 normal;
    float plane_depth;

    bool intersect(Ray r, Hit& hit) override;
private:
    void findNormal(Hit& hit) override;
};

