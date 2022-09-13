#include "IMaterial.h"

class Dielectric : public IMaterial
{
public:
    Dielectric(Color const& color, float refractionIndex) : m_color(color), m_refractionIndex(refractionIndex) {}

    Scattering scatter(Ray const& inputRay, Hit const& hit) const override;

private:
    float reflectance(float cosTheta) const;

private:
    Color m_color;
    float m_refractionIndex;
};