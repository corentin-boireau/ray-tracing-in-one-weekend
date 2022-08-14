#pragma once

#include "Vec3.h"
#include "Ray.h"

class Camera
{
public:
    Camera(float viewportWidth, float viewportHeight, float focalLength) :
        m_origin          (          0.f,            0.f, 0.f),
        m_horizontal      (viewportWidth,            0.f, 0.f),
        m_vertical        (          0.f, viewportHeight, 0.f),
        m_lowerLeftCorner (m_origin - m_horizontal/2 - m_vertical/2 - Vec3(0, 0, focalLength))
    {}

    inline Ray getRay(float u, float v) const { return Ray(m_origin, m_lowerLeftCorner + u*m_horizontal + v*m_vertical - m_origin); }

private:
    Point3 m_origin;
    Vec3   m_horizontal;
    Vec3   m_vertical;
    Point3 m_lowerLeftCorner;
};