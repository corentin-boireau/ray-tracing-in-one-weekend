#pragma once

#include <iostream>

#include "Vec3.h"
#include "Ray.h"
#include "utils.h"

class Camera
{
public:
    Camera(
        Point3 lookFrom,
        Point3 lookAt,
        Vec3   vUp,
        float  verticalFOV_deg,
        float  aspectRatio
    ):
        Camera(
            lookFrom, vUp, aspectRatio,
            unitVector(lookFrom - lookAt), // w
            // theta          = verticalFOV_deg converted to radians
            // h              = tan(theta/2) 
            // viewportHeight = 2h
            2.f * tan(utils::degrees_to_radians(verticalFOV_deg) / 2.f) // viewportHeight
        )
    {
        std::cout << "Camera: " << *this << "\n";
    }

    inline Ray getRay(float s, float t) const { return Ray(m_origin, m_lowerLeftCorner + s*m_horizontal + t*m_vertical - m_origin); }
    friend std::ostream& operator<<(std::ostream& os, Camera const& camera);

private:
    Point3 m_origin;
    Vec3   m_horizontal;
    Vec3   m_vertical;
    Point3 m_lowerLeftCorner;


private:
    // Delegate constructors
    Camera(
        Point3 lookFrom,
        Vec3   vUp,
        float  aspectRatio,
        Vec3   w,
        float  viewport_height
    ):
        Camera(
            lookFrom, w, viewport_height, aspectRatio,
            unitVector(cross(vUp, w)) // u
        )
    {}

    Camera(
        Point3 lookFrom,
        Vec3   w,
        float  vph,
        float  ratio,
        Vec3   u
    ):
        m_origin          (lookFrom),
        m_horizontal      (ratio * vph * u),
        m_vertical        (vph * cross(w, u)),
        m_lowerLeftCorner (m_origin - m_horizontal/2 - m_vertical/2 - w)
    {}
};

inline std::ostream& operator<<(std::ostream& os, Camera const& camera)
{
    return os
        <<   "origin: "          << camera.m_origin    
        << ", horizontal: "      << camera.m_horizontal
        << ", vertical: "        << camera.m_vertical  
        << ", lowerLeftCorner: " << camera.m_lowerLeftCorner;
}