#pragma once

#include <limits>
#include <random>

namespace utils
{
	// Constants
	
	const float infinity = std::numeric_limits<float>::infinity();
	const float pi       = 3.1415926535897932385f;
	
	// Utility Functions
	
	inline double degrees_to_radians(double degrees) { return degrees * pi / 180.0; }
	
	inline float randomFloat(float min, float max) 
	{
		static std::uniform_real_distribution<float> distribution(min, max);
		static std::mt19937 generator;
		return distribution(generator);
	}

	inline float randomFloat() { return randomFloat(0.f, 1.f); }
	
	inline float clamp(float x, float min, float max)
	{
		return (x < min) ? min
			 : (x > max) ? max
			 :             x;
	}
}