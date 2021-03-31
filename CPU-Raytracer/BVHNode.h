#pragma once
#include "BBox.h"
#include "Primitive.h"
#include "Hit.h"	
#include <vector>

class BVHNode
{
public:
	BVHNode(std::vector<Primitive*> geometry);
	BVHNode(Primitive* leaf_obj);
	~BVHNode();

	bool search(const Ray& r, Hit* hit_info) const;

private:
	BBox findBBox(const std::vector<Primitive*>& geometry) const;

	BVHNode* left = nullptr;
	BVHNode* right = nullptr;
	BBox AABB;
	Primitive* leaf = nullptr;
};

