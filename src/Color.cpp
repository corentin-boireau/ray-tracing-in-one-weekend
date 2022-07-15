#include "Color.h"

Color_uint8_t Color::to8bit()
{
    return Color_uint8_t {
        static_cast<uint8_t>(255.999f * m_red),
        static_cast<uint8_t>(255.999f * m_green),
        static_cast<uint8_t>(255.999f * m_blue)
    };
}
