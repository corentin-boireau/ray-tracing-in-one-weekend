#include "Color.h"

#include <cmath>

#include "utils.h"

Color Color::corrected(size_t nbOfSamples) const
{
    // Divide the color by the number of samples and gamma-correct for gamma = 2.0.
    float scale = 1.f / nbOfSamples;
    return Color(
        sqrt(scale * m_red),
        sqrt(scale * m_green),
        sqrt(scale * m_blue)
    );
}

Color_uint8_t Color::to8bit()
{
    return Color_uint8_t {
        static_cast<uint8_t>(255.999f * utils::clamp(m_red,   0.f, 1.0f)),
        static_cast<uint8_t>(255.999f * utils::clamp(m_green, 0.f, 1.0f)),
        static_cast<uint8_t>(255.999f * utils::clamp(m_blue,  0.f, 1.0f))
    };
}
