#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

#include <stb_image_write.h>

#include "Vec3.h"
#include "Color.h"

constexpr size_t IMAGE_WIDTH  = 2560;
constexpr size_t IMAGE_HEIGHT = 2560;
const     char*  OUT_FILENAME = "image.png";

int main()
{
    std::cout << "Ray Tracing in One Weekend !" << std::endl;

    std::vector<Color_uint8_t> imagePixels;
    imagePixels.reserve(IMAGE_WIDTH * IMAGE_HEIGHT);

    for (size_t i = 0; i < IMAGE_HEIGHT; i++)
    {
        std::cout << "\rRendering: " << i * 100 / IMAGE_HEIGHT << "%" << std::flush;
        for (size_t j = 0; j < IMAGE_WIDTH; j++) 
        {
            Color pixel(
                static_cast<float>(IMAGE_HEIGHT - i) / (IMAGE_HEIGHT - 1),
                static_cast<float>(j)                / (IMAGE_WIDTH - 1),
                0.25f
            );

            imagePixels.push_back(pixel.to8bit());
        }
    }
    std::cout << "\33[2K\rRendering: Done." << std::endl;
    
    stbi_write_png(OUT_FILENAME, IMAGE_WIDTH, IMAGE_HEIGHT, 3, imagePixels.data(), 0);
}