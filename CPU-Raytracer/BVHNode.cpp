#include "BVHNode.h"
#include "Ray.h"

bool BVHNode::search(const Ray& r, Hit& hit_info)
{
    Vec3 unused_parameter;
    if (!AABB.intersect(r, unused_parameter))
        return false;

    if (leaf != nullptr)
    {
        if (leaf->intersect(r, hit_info))
        {
            return true;
        }
    }

    bool collision;

    collision = left->search(r, hit_info);
    if (collision)
        return true;
    collision = right->search(r, hit_info);
    return collision;
}
