#include "../Vec3.h"
#include "IHittable.h"
#include "../materials/IMaterial.h"

class Sphere : public IHittable
{
public:
    Sphere(Point3 c, float r, mat_ptr material) :
        m_center(c), m_radius(r), m_material(material) {}

    inline Point3 const& center() const { return m_center; }
    inline float         radius() const { return m_radius; }

    bool hit(Ray const& ray, float tMin, float tMax, Hit& result) const override;
private:
    mat_ptr m_material;
    Point3  m_center;
    float   m_radius;
};