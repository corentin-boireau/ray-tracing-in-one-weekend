#include <iostream>
#include <fstream>
#include <vector>

#include <stb_image_write.h>

int main()
{
    std::cout << "Ray Tracing in One Weekend !" << std::endl;
    
    constexpr size_t imageWidth  = 256;
    constexpr size_t imageHeight = 256;

    std::vector<uint8_t> imageData;
    imageData.reserve(3 * imageWidth * imageHeight);

    for (size_t i = 0; i < imageWidth; i++) 
    {
        for (size_t j = 0; j < imageHeight; j++) 
        {
            double r = static_cast<double>(i) / (imageWidth - 1);
            double g = static_cast<double>(j) / (imageHeight - 1);
            double b = 0.25;

            uint8_t ir = static_cast<uint8_t>(255.999 * r);
            uint8_t ig = static_cast<uint8_t>(255.999 * g);
            uint8_t ib = static_cast<uint8_t>(255.999 * b);

            imageData.push_back(ir);
            imageData.push_back(ig);
            imageData.push_back(ib);
        }
    }
    
    stbi_write_png("image.png", imageWidth, imageHeight, 3, imageData.data(), 0);
}