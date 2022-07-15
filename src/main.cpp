#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <cmath>

#include <stb_image_write.h>

#include "Vec3.h"
#include "Color.h"
#include "Ray.h"
#include "Sphere.h"

const     char*  OUT_FILENAME = "image.png";

// Image
constexpr float  ASPECT_RATIO = 16.f / 9.f;
constexpr size_t IMAGE_WIDTH  = 1080;
constexpr size_t IMAGE_HEIGHT = static_cast<size_t>(IMAGE_WIDTH / ASPECT_RATIO);

// Camera
constexpr float VIEWPORT_HEIGHT = 2.0f;
constexpr float VIEWPORT_WIDTH  = VIEWPORT_HEIGHT * ASPECT_RATIO;
constexpr float FOCAL_LENGTH    = 1.0f;

const Sphere g_sphere(Point3(0.f, 0.f, -1.f), 0.5f);

bool doHitSphere(Ray const& ray, Sphere const& sphere)
{
    /*
        Let 
          C the center
         and 
          r the radius 
        of a sphere in this space.
                
        Let P(t) a ray
        P(t) = A + tb
        with 
          A the origin    of the ray
          b the direction of the ray
        
        P(t) is on the sphere if
            (P(t) - C) . (P(t) - C) = r²
        <=> (A + tb - C) . (A + tb - C) = r²
        <=> t²b . b + 2tb . (A - C) + (A - C) . (A - C) - r² = 0
        Identify to the form ax² + bx + c --> 
          a = (b . b)                = ||b||²
          b = 2b . (A - C)
          c = (A - C) . (A - C) - r² = ||(A - C)||² - r²
        And
          delta = b² - 4ac
    */
    Vec3 oc = ray.origin() - sphere.center();
    float a = ray.direction().length_squared();
    float b = 2 * dot(ray.direction(), oc);
    float c = oc.length_squared() - (sphere.radius() * sphere.radius());

    float delta = b * b - 4 * a * c;

    return delta > 0.f;
}

Color computeRayColor(Ray ray)
{
    Vec3 unitDirection = unitVector(ray.direction());
    float t = 0.5f * (unitDirection.y() + 1.f);
    Color color = doHitSphere(ray, g_sphere)
        ? Color(1.f, 0.f, 0.f)  // Red
        : (1.f - t) * Color(1.f, 1.f, 1.f) + t * Color(0.5f, 0.7f, 1.f);

    return color;
}

int main()
{
    std::cout << "Ray Tracing in One Weekend !" << std::endl;

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

            Color pixel = computeRayColor(ray);

            imagePixels.push_back(pixel.to8bit());
        }
    }
    std::cout << "\33[2K\rRendering: Done." << std::endl;
    
    stbi_write_png(OUT_FILENAME, IMAGE_WIDTH, IMAGE_HEIGHT, 3, imagePixels.data(), 0);
}