#pragma once

#include <iostream>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <array>

#include "utils.h"

class Vec3
{
public:
	Vec3() 
		: m_coordinates{ 0, 0, 0 } {}
	Vec3(float x, float y, float z)
		: m_coordinates{ x, y, z } {}

	static inline Vec3 random() { return Vec3(utils::randomFloat(), utils::randomFloat(), utils::randomFloat()); }
	static inline Vec3 random(float min, float max) 
	{
		return Vec3(utils::randomFloat(min, max), utils::randomFloat(min, max), utils::randomFloat(min, max)); 
	}

	inline float x() const { return m_coordinates[0]; }
	inline float y() const { return m_coordinates[1]; }
	inline float z() const { return m_coordinates[2]; }

	inline Vec3   operator-()       const { return Vec3(-m_coordinates[0], -m_coordinates[1], -m_coordinates[2]); }
	inline float  operator[](int i) const { return m_coordinates[i]; }
	inline float& operator[](int i)       { return m_coordinates[i]; }

	// Term operations with another vector
	inline Vec3& operator+=(Vec3 const& v)
	{
		m_coordinates[0] += v.m_coordinates[0];
		m_coordinates[1] += v.m_coordinates[1];
		m_coordinates[2] += v.m_coordinates[2];
		return *this;
	}

	inline Vec3& operator-=(Vec3 const& v)
	{
		m_coordinates[0] -= v.m_coordinates[0];
		m_coordinates[1] -= v.m_coordinates[1];
		m_coordinates[2] -= v.m_coordinates[2];
		return *this;
	}

	inline Vec3& operator*=(Vec3 const& v)
	{
		m_coordinates[0] *= v.m_coordinates[0];
		m_coordinates[1] *= v.m_coordinates[1];
		m_coordinates[2] *= v.m_coordinates[2];
		return *this;
	}

	// Operations with scalar
	inline Vec3& operator*=(float f)
	{
		m_coordinates[0] *= f;
		m_coordinates[1] *= f;
		m_coordinates[2] *= f;
		return *this;
	}

	inline Vec3& operator/=(float f)
	{
		m_coordinates[0] /= f;
		m_coordinates[1] /= f;
		m_coordinates[2] /= f;
		return *this;
	}

	inline bool isNearZero() const 
	{
		constexpr float threshold = 1e-8;
		return std::all_of(m_coordinates.begin(), m_coordinates.end(),
			[](float f) { return fabs(f) < threshold; }
		);
	}

	inline float length_squared() const { return std::inner_product(m_coordinates.begin(), m_coordinates.end(), m_coordinates.begin(), 0.f); }
	inline float length()         const { return sqrt(length_squared()); }

	friend float dot(Vec3 const& u, Vec3 const& v);

protected:
	std::array<float, 3> m_coordinates;
};

inline std::ostream& operator<<(std::ostream &out, Vec3 const& v) 
{
	out << "(" << v.x() << " ," << v.y() << " ," << v.z() << ")";
	return out;
}

using Point3 = Vec3;

inline Vec3 operator+(Vec3 const& u, Vec3 const& v) { return Vec3(u) += v; }
inline Vec3 operator-(Vec3 const& u, Vec3 const& v) { return Vec3(u) -= v; }
inline Vec3 operator*(Vec3 const& u, Vec3 const& v) { return Vec3(u) *= v; }
inline Vec3 operator*(float f, Vec3 const& v)       { return Vec3(v) *= f; }
inline Vec3 operator*(Vec3 const& v, float f)       { return Vec3(v) *= f; }
inline Vec3 operator/(Vec3 const& v, float f)       { return Vec3(v) /= f; }

inline float dot(Vec3 const& u, Vec3 const& v) 
{ 
	return std::inner_product(u.m_coordinates.begin(), u.m_coordinates.end(), v.m_coordinates.begin(), 0.f);
}

inline Vec3 cross(Vec3 const& u, Vec3 const& v)
{
	return Vec3(
		u.y() * v.z() - u.z() * v.y(),
		u.z() * v.x() - u.x() * v.z(),
		u.x() * v.y() - u.y() * v.x()
	);
}

inline Vec3 unitVector(Vec3 const& v) 
{
	return v / v.length();
}

Point3 randomPointInUnitSphere();
inline Point3 randomPointOnUnitSphere() { return unitVector(randomPointInUnitSphere()); }
inline Vec3 randomUnitVector() { return unitVector(randomPointInUnitSphere()); }
