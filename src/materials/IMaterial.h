#pragma once

#include "../Ray.h"
#include "../Color.h"
#include "../hittables/IHittable.h"

struct Scattering
{
    Scattering(bool hasSctrd, Color att, Ray newRay) : hasScattered(hasSctrd), attenuation(att), scatteredRay(newRay) {}

    bool  hasScattered;
    Color attenuation;
    Ray   scatteredRay;
};

class IMaterial
{
public:
    virtual Scattering scatter(Ray const& inputRay, Hit const& hit) const = 0;
};