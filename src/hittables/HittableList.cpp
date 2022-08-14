#include "HittableList.h"

bool HittableList::hit(Ray const& ray, float tMin, float tMax, Hit& result) const
{
    Hit hit;
    bool hasHitAnything = false;
    float closest = tMax;

    for (auto const& hittable : m_hittables)
    {
        if (hittable->hit(ray, tMin, closest, hit))
        {
            hasHitAnything = true;
            closest = hit.t;
            result = hit;
        }
    }

    return hasHitAnything;
}