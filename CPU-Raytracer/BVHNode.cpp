#include "BVHNode.h"
#include "Ray.h"
#include <algorithm>
#include <iostream>

BVHNode::BVHNode(std::vector<Primitive*> geometry)
{
    // are we a leaf?
    if (geometry.size() == 1)
    {
        leaf = geometry.back();
        AABB = leaf->getBBox();
        return;
    }
    // find our BBox
    AABB = findBBox(geometry);
    float surface_area = AABB.surfaceArea();
    // calculate the geom split
    std::vector<Primitive*> ordered = geometry;
    std::vector<Primitive*> left_split;
    std::vector<Primitive*> right_split;
    float best_cost = 100000000;
    for (int axis = 0; axis < 3; ++axis)
    {
        std::sort(ordered.begin(), ordered.end(), [axis](Primitive* obj_a, Primitive* obj_b) { return obj_a->o()[axis] > obj_b->o()[axis]; });
        for (int i = 1; i < ordered.size(); ++i)
        {
            std::vector<Primitive*> l_split(ordered.begin(), ordered.begin() + i);
            std::vector<Primitive*> r_split(ordered.begin() + i, ordered.end());
            BBox LBB = findBBox(l_split);
            BBox RBB = findBBox(l_split);
            float p_l = LBB.surfaceArea() / surface_area;
            float p_r = RBB.surfaceArea() / surface_area;
            // assuming all elements have the same intersect cost
            float cost = 0.5f + p_l * l_split.size() + p_r * r_split.size();
            if (cost < best_cost)
            {
                best_cost = cost;
                left_split = l_split;
                right_split = r_split;
            }
        }
    }

    //for( each split )
    //{
    //  float leaf_cost = 0;
    //  for(int i = 0; i < N; ++i)
    //  {
            // WHAT IS T??????? cost of intersecting a triangle????
    //      leaf_cost += t;
    //  }
    //}

    // build lower nodes
    left = new BVHNode(left_split);
    right = new BVHNode(right_split);
}

BVHNode::BVHNode(Primitive* leaf_obj) :
    AABB(leaf_obj->getBBox())
{
    leaf = leaf_obj;
}

BVHNode::~BVHNode()
{
    if (left)
    {
        delete left;
        left = nullptr;
    }
    if (right)
    {
        delete right;
        right = nullptr;
    }
    // Yes I know this is a memory leak, but it crashes on leaf=nullptr FOR SOME REASON?!
    // primitives could be deleted using the vector in main.cpp potentially
    //if (leaf)
    //{
    //    delete leaf;
    //    leaf = nullptr;
    //}
}

bool BVHNode::search(const Ray& r, Hit& hit_info) const
{
    Vec3 unused_parameter;
    if (!AABB.intersect(r, unused_parameter))
        return false;

    if (leaf != nullptr)
    {
        return leaf->intersect(r, hit_info);
    }

    bool col_l = left->search(r, hit_info);
    bool col_r = right->search(r, hit_info);
    return  col_l || col_r;
}

void BVHNode::debug(int& id, int& depth) const
{
    depth++;
    id++;
    if (leaf)
    {
        std::cout << depth << " - " << id << ":\tLeaf\nUP" << std::endl;
        depth--;
        return;
    }
    std::cout << "LEFT: ";
    left->debug(id, depth);
    std::cout << "RIGHT: ";
    right->debug(id, depth);
    std::cout << "UP" << std::endl;
}

BBox BVHNode::findBBox(const std::vector<Primitive*>& geometry) const
{
    Vec3 mins;
    mins = geometry[0]->getBBox().getMins();
    Vec3 maxs;
    maxs = geometry[0]->getBBox().getMax();
    for (auto prim : geometry)
    {
        //Vec3 i_mins = prim->getBBox().getMins();
        //if (i_mins.x() < mins.x())
        //    mins.x() = i_mins.x();
        //if (i_mins.y() < mins.y())
        //    mins.y() = i_mins.y();
        //if (i_mins.z() < mins.z())
        //    mins.z() = i_mins.z();
        mins = Vec::min(prim->getBBox().getMins(), mins);

        //Vec3 i_maxs = prim->getBBox().getMax();
        //if (i_maxs.x() > maxs.x())
        //    maxs.x() = i_maxs.x();
        //if (i_maxs.y() > maxs.y())
        //    maxs.y() = i_maxs.y();
        //if (i_maxs.z() > maxs.z())
        //    maxs.z() = i_maxs.z();
        maxs = Vec::max(prim->getBBox().getMax(), maxs);
    }
    return BBox(mins, maxs);
}
