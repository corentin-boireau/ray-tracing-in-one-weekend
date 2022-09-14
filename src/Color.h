#pragma once

#include <cstdint>

#include "Vec3.h"

struct Color_uint8_t
{
    uint8_t r, g, b;
};

class Color : public Vec3
{
public:
    constexpr Color(float r, float g, float b) : Vec3(r, g, b) {}
    constexpr Color(Vec3 const& v)  : Vec3(v) {}  // Used for implicit conversion
    constexpr Color(Color const& c) = default;
    inline Color& operator=(Color const& c) = default;


    inline float r() const { return Vec3::m_coordinates[0]; }
    inline float g() const { return Vec3::m_coordinates[1]; }
    inline float b() const { return Vec3::m_coordinates[2]; }

    inline operator Vec3() const { return static_cast<Vec3>(*this); }
    
    Color corrected(size_t nbOfSamples) const;
    Color_uint8_t to8bit();

private:
    inline float& r() { return Vec3::m_coordinates[0]; }
    inline float& g() { return Vec3::m_coordinates[1]; }
    inline float& b() { return Vec3::m_coordinates[2]; }
};
