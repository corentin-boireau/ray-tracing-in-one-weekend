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
      P(t) = A + tb
    with 
      A the origin    of the ray
      b the direction of the ray

    P(t) is on the sphere if
        (P(t) - C) . (P(t) - C) = r�
    <=> (A + tb - C) . (A + tb - C) = r�
    <=> t�b . b + 2tb . (A - C) + (A - C) . (A - C) - r� = 0
    Identify to the form ax� + bx + c --> 
      a = (b . b)                = ||b||�
      b = 2b . (A - C)           = 2 (b . (A -C))
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
    Vec3 oc = ray.origin() - m_center;
    float a = ray.direction().length_squared();
    float h = dot(ray.direction(), oc);
    float c = oc.length_squared() - (m_radius * m_radius);

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
        }
    }
    
    return hasHit;
}