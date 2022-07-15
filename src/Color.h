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

	inline float red()   const { return x(); }
	inline float green() const { return y(); }
	inline float blue()  const { return z(); }

	inline operator Vec3() const { return static_cast<Vec3>(*this); }
	
	Color_uint8_t to8bit();
};
