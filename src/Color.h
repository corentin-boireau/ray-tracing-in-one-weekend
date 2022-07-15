#pragma once

#include <cstdint>

struct Color_uint8_t
{
	uint8_t r, g, b;
};

class Color
{
public:
	Color(float r, float g, float b) : m_red(r), m_green(g), m_blue(b) {}
	
	Color_uint8_t to8bit();
private:
	float m_red, m_green, m_blue;
};
