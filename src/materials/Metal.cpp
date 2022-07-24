#include "Metal.h"

Scattering Metal::scatter(Ray const& inputRay, Hit const& hit) const
{
	Vec3 reflectedDirection = reflect(inputRay.direction(), hit.normal);
	return Scattering(
		dot(reflectedDirection, hit.normal) > 0,  // If this is negative, the ray was coming from the inside of the surface so we have to ignore it
		m_albedo,
		Ray(hit.p, reflectedDirection)
	);
}