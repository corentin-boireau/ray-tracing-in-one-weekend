#pragma once

#include "IMaterial.h"

class Metal : public IMaterial
{
public:
	Metal(Color const& albedo) : m_albedo(albedo) {}

	Scattering scatter(Ray const& inputRay, Hit const& hit) const override;
private:
	Color m_albedo;
};