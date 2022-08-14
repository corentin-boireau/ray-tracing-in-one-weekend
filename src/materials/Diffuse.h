#pragma once

#include "IMaterial.h"

class Diffuse : public IMaterial
{
public:
    Diffuse(Color const& albedo) : m_albedo(albedo) {}

    Scattering scatter(Ray const& inputRay, Hit const& hit) const override;
private:
    Color m_albedo;
};