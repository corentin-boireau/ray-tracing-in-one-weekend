#pragma once

#include "IHittable.h"

#include <memory>
#include <vector>

class HittableList : public IHittable
{
public:
    HittableList() {}
    HittableList(std::shared_ptr<IHittable> hittable) { add(hittable); }

    inline void clear() { m_hittables.clear(); }
    inline void add(std::shared_ptr<IHittable> hittable) { m_hittables.push_back(hittable); }

    bool hit(Ray const& ray, float tMin, float tMax, Hit& result) const override;
private:
    std::vector<std::shared_ptr<IHittable>> m_hittables;
};