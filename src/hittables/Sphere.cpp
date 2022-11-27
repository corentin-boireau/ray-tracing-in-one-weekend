#include "Sphere.h"

bool Sphere::hit(Ray const& ray, float tMin, float tMax, Hit& result) const
{
    /*
    Let 
      C the center
    and 
      r the radius 
    of a sphere in this space.

    Let P(t) a ray
      P(t) = A + tB
    with 
      A the origin    of the ray
      B the direction of the ray

    P(t) is on the sphere if
        (P(t) - C) . (P(t) - C) = r�
    <=> (A + tB - C) . (A + tB - C) = r�
    <=> t�B . B + 2tB . (A - C) + (A - C) . (A - C) - r� = 0
    Identify to the form ax� + bx + c --> 
      a = (B . B)                = ||B||�
      b = 2B . (A - C)           = 2 (B . (A -C))
      c = (A - C) . (A - C) - r� = ||(A - C)||� - r�
    And
      delta = b� - 4ac

    So
        t = (-b - sqrt(delta)) / (2a)
      Let h = b/2
    <=> t = (-2h - sqrt((2h)� - 4ac)) / (2a)
    <=> t = (-2h - 2 sqrt((h� - ac)) / (2a)
    <=> t = (-h - sqrt((h� - ac)) / a
    */
    Vec3 oc = ray.origin() - m_center;  // A - C
    float a = ray.direction().lengthSquared();
    float h = dot(ray.direction(), oc);
    float c = oc.lengthSquared() - (m_radius * m_radius);

    float delta = h*h - a*c;

    bool hasHit = false;
    if (delta > 0.f)
    {
        float root = (-h - sqrt(delta)) / a;
        if (root < tMin || root > tMax)
            root = (-h + sqrt(delta)) / a;
        
        hasHit = root > tMin && root < tMax;
        if (hasHit)
        {
            result.t = root;
            result.p = ray.at(result.t);
            Vec3 outwardNormal = unitVector(result.p - m_center);
            result.setFaceNormal(ray, outwardNormal);
            result.material = m_material;
        }
    }
    
    return hasHit;
}