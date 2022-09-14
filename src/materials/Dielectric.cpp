#include "Dielectric.h"

constexpr float AIR_REFRACTION_INDEX = 1.f;

Scattering Dielectric::scatter(Ray const& inputRay, Hit const& hit) const
{
    double refractionRatio = hit.isFrontFace
        ? AIR_REFRACTION_INDEX / m_refractionIndex
        : m_refractionIndex    / AIR_REFRACTION_INDEX;

    Vec3 unitDirection = unitVector(inputRay.direction());
    float cosTheta = fmin(dot(-unitDirection, hit.normal), 1.f);
    float sinTheta = sqrt(1 - cosTheta * cosTheta);

    bool canRefract = refractionRatio * sinTheta <= 1.f;

    return Scattering(
        true,
        m_color,
        Ray(hit.p, canRefract && reflectance(cosTheta) < utils::randomFloat()
            ? refract(unitDirection, hit.normal, refractionRatio)
            : reflect(unitDirection, hit.normal)
        )
    );
}

float Dielectric::reflectance(float cosTheta) const
{ // Use Schlick's approximation for reflectance
    float const& n1 = AIR_REFRACTION_INDEX;
    float const& n2 = m_refractionIndex;

    float r0 = pow((n1 - n2) / (n1 + n2), 2);
    // r0 is the reflection coefficient of a ray that is parallel to the normal, i.e. when theta = 0

    return r0 + (1.f - r0) * static_cast<float>(pow(1.f - cosTheta, 5));
}
