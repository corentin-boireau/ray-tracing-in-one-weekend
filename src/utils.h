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
	
	inline float randomFloat()
	{
		static std::uniform_real_distribution<float> distribution(0.f, 1.f);
		static std::mt19937 generator;
		return distribution(generator);
	}
		
}