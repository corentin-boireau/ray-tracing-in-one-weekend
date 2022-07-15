#include "Vec3.h"

class Sphere
{
public:
	Sphere(Point3 c, float r) : m_center(c), m_radius(r) {}

	inline Point3 const& center() const { return m_center; }
	inline float         radius() const { return m_radius; }
private:
	Point3 m_center;
	float  m_radius;
};