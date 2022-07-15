#include "Vec3.h"
#include "Hittable.h"

class Sphere : public IHittable
{
public:
	Sphere(Point3 c, float r) : m_center(c), m_radius(r) {}

	inline Point3 const& center() const { return m_center; }
	inline float         radius() const { return m_radius; }

	bool hit(Ray const& ray, float tMin, float tMax, Hit& result) const override;
private:
	Point3 m_center;
	float  m_radius;
};