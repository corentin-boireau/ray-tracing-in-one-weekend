#include "Diffuse.h"

#include "../Vec3.h"
#include "../utils.h"

Scattering Diffuse::scatter(Ray const& inputRay, Hit const& hit) const
{
    Vec3 newDirection = hit.normal + randomUnitVector();
    
    // Catch degenerate scatter direction
    if (newDirection.isNearZero())
        newDirection = hit.normal;

    return Scattering(
        true,
        m_albedo,
        Ray(hit.p, newDirection)
    );
}