#pragma once

#include "Vec3.h"

class Ray
{
public:
    Ray() {}
    Ray(Point3 const& origin, Vec3 const& direction)
        : m_origin(origin), m_direction(direction) {}

    inline Point3 origin()    const { return m_origin; }
    inline Vec3   direction() const { return m_direction; }

    inline Point3 at(float t) const { return m_origin + t * m_direction; }

private:
    Point3 m_origin;
    Vec3   m_direction;
};