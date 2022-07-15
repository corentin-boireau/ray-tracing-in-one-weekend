#include "Color.h"

Color_uint8_t Color::to8bit()
{
    return Color_uint8_t {
        static_cast<uint8_t>(255.999f * red()),
        static_cast<uint8_t>(255.999f * green()),
        static_cast<uint8_t>(255.999f * blue())
    };
}
