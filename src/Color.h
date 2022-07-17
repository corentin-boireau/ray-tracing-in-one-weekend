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
	Color(float r, float g, float b) : Vec3(r, g, b) {}
	Color(Vec3 const& v) : Vec3(v) {}  // Used for implicit conversion

	inline float r() const { return m_red; }
	inline float g() const { return m_green; }
	inline float b() const { return m_blue; }

	inline operator Vec3() const { return static_cast<Vec3>(*this); }
	
	Color corrected(size_t nbOfSamples) const;
	Color_uint8_t to8bit();

private:
	float& m_red   = Vec3::m_coordinates[0];
	float& m_green = Vec3::m_coordinates[1];
	float& m_blue  = Vec3::m_coordinates[2];
};
