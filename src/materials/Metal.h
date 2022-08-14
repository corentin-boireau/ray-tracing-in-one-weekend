#pragma once

#include <cassert>

#include "IMaterial.h"

class Metal : public IMaterial
{
public:
    Metal(Color const& albedo, float fuzziness) :
        m_albedo(albedo),
        m_fuzziness(fuzziness)
    {
        assert(0.f <= fuzziness && fuzziness <= 1.f);
    }

    Scattering scatter(Ray const& inputRay, Hit const& hit) const override;
private:
    Color m_albedo;
    float m_fuzziness;
};