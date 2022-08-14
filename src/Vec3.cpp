#include "Vec3.h"

Point3 randomPointInUnitSphere()
{
    Vec3 v = Vec3::random(-1.f, 1.f);

    while (v.lengthSquared() > 1.f)
        v = Vec3::random(-1.f, 1.f);

    return v;
}

Vec3 refract(Vec3 const& vIn, Vec3 const& normal, float refractionRatio)
{
    float cosTheta = fmin(dot(-vIn, normal), 1.f);
    Vec3 vOutPerpendicular = refractionRatio * (vIn + dot(-vIn, normal) * normal);
    Vec3 vOutParallel      = -sqrt(1 - vOutPerpendicular.lengthSquared()) * normal;
    return vOutPerpendicular + vOutParallel;
}
