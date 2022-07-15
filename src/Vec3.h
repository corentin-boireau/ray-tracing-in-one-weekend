#pragma once

#include <iostream>

#include <cmath>
#include <numeric>

class Vec3
{
public:
	Vec3() 
		: e{ 0, 0, 0 } {}
	Vec3(float e0, float e1, float e2)
		: e{ e0, e1, e2 } {}

	inline float x() const { return e[0]; }
	inline float y() const { return e[1]; }
	inline float z() const { return e[2]; }

	inline Vec3   operator-()       const { return Vec3(-e[0], -e[1], -e[2]); }
	inline float  operator[](int i) const { return e[i]; }
	inline float& operator[](int i)       { return e[i]; }

	// Term operations with another vector
	inline Vec3& operator+=(Vec3 const& v)
	{
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;
	}

	inline Vec3& operator-=(Vec3 const& v)
	{
		e[0] -= v.e[0];
		e[1] -= v.e[1];
		e[2] -= v.e[2];
		return *this;
	}

	inline Vec3& operator*=(Vec3 const& v)
	{
		e[0] *= v.e[0];
		e[1] *= v.e[1];
		e[2] *= v.e[2];
		return *this;
	}

	// Operations with scalar
	inline Vec3& operator*=(float f)
	{
		e[0] *= f;
		e[1] *= f;
		e[2] *= f;
		return *this;
	}

	inline Vec3& operator/=(float f)
	{
		e[0] /= f;
		e[1] /= f;
		e[2] /= f;
		return *this;
	}

	inline float length_squared() const { return e[0]*e[0] + e[1]*e[1] + e[2]*e[2]; }
	inline float length()         const { return sqrt(length_squared()); }

	friend float dot(Vec3 const& u, Vec3 const& v);
private:
	float e[3];
};

inline std::ostream& operator<<(std::ostream &out, const Vec3 &v) 
{
	out << "(" << v.x() << " ," << v.y() << " ," << v.z() << ")";
	return out;
}

inline Vec3 operator+(Vec3 const& u, Vec3 const& v) { return Vec3(u) += v; }
inline Vec3 operator-(Vec3 const& u, Vec3 const& v) { return Vec3(u) -= v; }
inline Vec3 operator*(Vec3 const& u, Vec3 const& v) { return Vec3(u) *= v; }
inline Vec3 operator*(float f, Vec3 const& v)       { return Vec3(v) *= f; }
inline Vec3 operator*(Vec3 const& v, float f)       { return Vec3(v) *= f; }
inline Vec3 operator/(Vec3 const& v, float f)       { return Vec3(v) /= f; }

inline float dot(Vec3 const& u, Vec3 const& v) 
{ 
	return std::inner_product(u.e, u.e + 3, v.e, 0.f); 
}

inline Vec3 cross(Vec3 const& u, Vec3 const& v)
{
	return Vec3(
		u.y() * v.z() - u.z() * v.y(),
		u.z() * v.x() - u.x() * v.z(),
		u.x() * v.y() - u.y() * v.x()
	);
}

inline Vec3 unit_vector(Vec3 const& v) 
{
	return v / v.length();
}