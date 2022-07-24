#include <iostream>
#include <vector>
#include <memory>

#include <stb_image_write.h>

#include "utils.h"

#include "Vec3.h"
#include "Color.h"
#include "Ray.h"
#include "Camera.h"

#include "hittables/IHittable.h"
#include "hittables/HittableList.h"
#include "hittables/Sphere.h"

#include "materials/IMaterial.h"
#include "materials/Diffuse.h"


const char* OUT_FILENAME = "image.png";

// Image
constexpr float  ASPECT_RATIO = 16.f / 9.f;
constexpr size_t IMAGE_WIDTH  = 720;
constexpr size_t IMAGE_HEIGHT = static_cast<size_t>(IMAGE_WIDTH / ASPECT_RATIO);

// Camera
constexpr float VIEWPORT_HEIGHT = 2.0f;
constexpr float VIEWPORT_WIDTH  = VIEWPORT_HEIGHT * ASPECT_RATIO;
constexpr float FOCAL_LENGTH    = 1.0f;

constexpr size_t SAMPLES_BY_PIXEL = 100;
constexpr size_t MAX_RAY_BOUNCES  = 50;


Color computeRayColor(Ray const& ray, IHittable const& hittable, size_t remainingBounces)
{
    if (remainingBounces <= 0)
        return Color(0.f, 0.f, 0.f);

    Hit hit;
    if (hittable.hit(ray, 0.001f, utils::infinity, hit))
    {
        Scattering scattering = hit.material->scatter(ray, hit);
        return scattering.hasScattered
            ? scattering.attenuation * computeRayColor(scattering.scatteredRay, hittable, remainingBounces - 1)
            : Color(0, 0, 0);
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

    // Materials
    std::shared_ptr<Diffuse> diffuseRed   = std::make_shared<Diffuse>(Color(.8f, 0.f, 0.f));
    std::shared_ptr<Diffuse> diffuseGreen = std::make_shared<Diffuse>(Color(0.f, .8f, 0.f));
    std::shared_ptr<Diffuse> diffuseBlue  = std::make_shared<Diffuse>(Color(0.f, 0.f, .8f));


    // World
    HittableList worldObjects;
    worldObjects.add(std::make_shared<Sphere>(Point3( 0.0f,    0.0f, -1.0f),   0.5f, diffuseRed));
    worldObjects.add(std::make_shared<Sphere>(Point3( 0.1f,    0.2f, -0.5f),   0.1f, diffuseBlue));
    worldObjects.add(std::make_shared<Sphere>(Point3( 0.0f, -100.5f, -1.0f), 100.0f, diffuseGreen));

    // Camera
    Camera camera(VIEWPORT_WIDTH, VIEWPORT_HEIGHT, FOCAL_LENGTH);
    
    // Rendering
    std::vector<Color_uint8_t> imagePixels;
    imagePixels.reserve(IMAGE_WIDTH * IMAGE_HEIGHT);

    for (size_t i = 0; i < IMAGE_HEIGHT; i++)
    {
        std::cout << "\rRendering: " << i * 100 / IMAGE_HEIGHT << "%" << std::flush;
        for (size_t j = 0; j < IMAGE_WIDTH; j++) 
        {
            Color pixel(0.f, 0.f, 0.f);
            for (size_t s = 0; s < SAMPLES_BY_PIXEL; s++)
            {
                Ray ray = camera.getRay(
                    (static_cast<float>(j)                + utils::randomFloat()) / (IMAGE_WIDTH - 1),
                    (static_cast<float>(IMAGE_HEIGHT - i) + utils::randomFloat()) / (IMAGE_HEIGHT - 1)
                );

                pixel += computeRayColor(ray, worldObjects, MAX_RAY_BOUNCES);
                
            }
            imagePixels.push_back(pixel.corrected(SAMPLES_BY_PIXEL).to8bit());
        }
    }
    std::cout << "\33[2K\rRendering: Done." << std::endl;
    
    stbi_write_png(OUT_FILENAME, IMAGE_WIDTH, IMAGE_HEIGHT, 3, imagePixels.data(), 0);
}