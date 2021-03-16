#pragma once
#include "BBox.h"
#include "Primitive.h"
#include "Hit.h"	
#include <vector>

class BVHNode
{
public:
	BVHNode(Primitive* leaf_obj);
	BVHNode(std::vector<Primitive*> geometry);

	bool search(const Ray& r, Hit& hit_info);

private:
	BVHNode* left;
	BVHNode* right;
	BBox AABB;
	Primitive* leaf;
};

