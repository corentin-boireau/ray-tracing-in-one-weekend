#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <limits>
#include <cstdint>
#include <cmath>

#include <stb_image_write.h>

#include "Vec3.h"
#include "Color.h"
#include "Ray.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Sphere.h"

const char* OUT_FILENAME = "image.png";

// Image
constexpr float  ASPECT_RATIO = 16.f / 9.f;
constexpr size_t IMAGE_WIDTH  = 1080;
constexpr size_t IMAGE_HEIGHT = static_cast<size_t>(IMAGE_WIDTH / ASPECT_RATIO);

// Camera
constexpr float VIEWPORT_HEIGHT = 2.0f;
constexpr float VIEWPORT_WIDTH  = VIEWPORT_HEIGHT * ASPECT_RATIO;
constexpr float FOCAL_LENGTH    = 1.0f;

Color computeRayColor(Ray const& ray, IHittable const& hittable)
{
    Hit hit;
    if (hittable.hit(ray, 0, std::numeric_limits<float>::infinity(), hit))
    {
        return 0.5f * (Color(1, 1, 1) + hit.normal);
    }
    else
    {
        Vec3 unitDirection = unitVector(ray.direction());
        float t = 0.5f * (unitDirection.y() + 1.0f);
        return (1.f - t) * Color(1.0f, 1.0f, 1.0f) 
             + t         * Color(0.5f, 0.7f, 1.0f);
    }
}

int main()
{
    std::cout << "Ray Tracing in One Weekend !" << std::endl;

    // World
    HittableList worldObjects;
    worldObjects.add(std::make_shared<Sphere>(Point3( 0.0f,    0.0f, -1.0f),   0.5f));
    worldObjects.add(std::make_shared<Sphere>(Point3( 0.1f,    0.2f, -0.5f),   0.1f));
    worldObjects.add(std::make_shared<Sphere>(Point3( 0.0f, -100.5f, -1.0f), 100.0f));

    // Camera
    Point3 origin     (           0.f,             0.f, 0.f);
    Vec3   horizontal (VIEWPORT_WIDTH,             0.f, 0.f);
    Vec3   vertical   (           0.f, VIEWPORT_HEIGHT, 0.f);

    Point3 lowerLeftCorner = origin - horizontal/2 - vertical/2 - Vec3(0.f, 0.f, FOCAL_LENGTH);

    // Rendering
    std::vector<Color_uint8_t> imagePixels;
    imagePixels.reserve(IMAGE_WIDTH * IMAGE_HEIGHT);

    for (size_t i = 0; i < IMAGE_HEIGHT; i++)
    {
        std::cout << "\rRendering: " << i * 100 / IMAGE_HEIGHT << "%" << std::flush;
        for (size_t j = 0; j < IMAGE_WIDTH; j++) 
        {
            float u = static_cast<float>(j)                / (IMAGE_WIDTH - 1);
            float v = static_cast<float>(IMAGE_HEIGHT - i) / (IMAGE_HEIGHT - 1);

            Ray ray(
                origin,
                lowerLeftCorner + u * horizontal + v * vertical - origin
            );

            Color pixel = computeRayColor(ray, worldObjects);

            imagePixels.push_back(pixel.to8bit());
        }
    }
    std::cout << "\33[2K\rRendering: Done." << std::endl;
    
    stbi_write_png(OUT_FILENAME, IMAGE_WIDTH, IMAGE_HEIGHT, 3, imagePixels.data(), 0);
}