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
#include "materials/Metal.h"
#include "materials/Dielectric.h"


const char* OUT_FILENAME = "image.png";

// Image
constexpr float  ASPECT_RATIO = 16.f / 9.f;
constexpr size_t IMAGE_WIDTH  = 1200;
constexpr size_t IMAGE_HEIGHT = static_cast<size_t>(IMAGE_WIDTH / ASPECT_RATIO);

// Camera
constexpr float  VERTICAL_FOV_DEG = 30.0f;
constexpr Point3 LOOK_FROM        = Point3 (13.f, 2.f, 3.f);
constexpr Point3 LOOK_AT          = Point3 ( 0.f, 0.f, 0.f);
constexpr Vec3   VIEW_UP          = Vec3   ( 0.f, 1.f, 0.f);

constexpr size_t SAMPLES_BY_PIXEL = 500;
constexpr size_t MAX_RAY_BOUNCES  = 50;

HittableList randomScene() 
{
    HittableList world;

    mat_ptr groundMaterial = std::make_shared<Diffuse>(Color(0.5f, 0.5f, 0.5f));
    world.add(std::make_shared<Sphere>(Point3(0.f, -1000.f, 0.f), 1000, groundMaterial));

    for (int a = -11; a < 11; a++) 
    {
        for (int b = -11; b < 11; b++) 
        {
            float chooseMat = utils::randomFloat();
            Point3 center(a + 0.9f * utils::randomFloat(), 0.2f, b + 0.9f * utils::randomFloat());

            if ((center - Point3(4, 0.2, 0)).length() > 0.9) 
            {
                world.add(std::make_shared<Sphere>(center, 0.2f, 
                    chooseMat < 0.80f ? static_cast<mat_ptr>(std::make_shared<Diffuse>    (Color::random() * Color::random())                   ) :
                    chooseMat < 0.95f ? static_cast<mat_ptr>(std::make_shared<Metal>      (Color::random(0.5f, 1.f), utils::randomFloat(0.f, 0.5f))) :
                                        static_cast<mat_ptr>(std::make_shared<Dielectric> (Color::random(0.8f, 1.f), 1.5f)                      ) 
                ));
            }
        }
    }

    mat_ptr material1 = std::make_shared<Dielectric>(Color(1.f, 1.f, 1.f), 1.5f);
    world.add(std::make_shared<Sphere>(Point3(0.f, 1.f, 0.f), 1.0f, material1));

    mat_ptr material2 = std::make_shared<Diffuse>(Color(0.4, 0.2, 0.1));
    world.add(std::make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

    mat_ptr material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

    return world;
}


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
    std::shared_ptr<Diffuse>     diffuseRed   = std::make_shared<Diffuse>    (Color(.8f, 0.f, 0.f));
    std::shared_ptr<Diffuse>     diffuseGreen = std::make_shared<Diffuse>    (Color(0.f, .8f, 0.f));
    std::shared_ptr<Diffuse>     diffuseBlue  = std::make_shared<Diffuse>    (Color(0.f, 0.f, .8f));
    std::shared_ptr<Metal>       metalRed     = std::make_shared<Metal>      (Color(.8f, .3f, .3f), 0.3f);
    std::shared_ptr<Metal>       metalGreen   = std::make_shared<Metal>      (Color(.3f, .8f, .3f), 0.0f);
    std::shared_ptr<Metal>       metalBlue    = std::make_shared<Metal>      (Color(.3f, .3f, .8f), 1.0f);
    std::shared_ptr<Dielectric>  glassRed     = std::make_shared<Dielectric> (Color(1.f, .6f, .6f), 1.5f);
    std::shared_ptr<Dielectric>  glassBlue    = std::make_shared<Dielectric> (Color(.6f, .6f, 1.f), 1.5f);
    std::shared_ptr<Dielectric>  glassWhite   = std::make_shared<Dielectric> (Color(1.f, 1.f, 1.f), 1.5f);

    // auto material_ground = std::make_shared<Diffuse>     (Color(.8f, .8f, .0f));
    // auto material_center = std::make_shared<Diffuse>     (Color(.1f, .2f, .5f));
    // auto material_left   = std::make_shared<Diaelectric> (Color(1.f, 1.f, 1.f), 1.5f);
    // auto material_right  = std::make_shared<Metal>       (Color(.8f, .6f, .2f), 0.f);

    // World
    HittableList worldObjects = randomScene();
    // worldObjects.add(std::make_shared<Sphere>(Point3( 0.0f,    0.0f, -1.0f),   0.5f, diffuseRed));
    // worldObjects.add(std::make_shared<Sphere>(Point3(-0.7f,   -0.2f, -0.7f),   0.3f, metalGreen));
    // worldObjects.add(std::make_shared<Sphere>(Point3( 0.1f,    0.2f, -0.4f),   0.1f, glassBlue));
    // worldObjects.add(std::make_shared<Sphere>(Point3( 0.0f, -100.5f, -1.0f), 100.0f, diffuseGreen));

    // worldObjects.add(std::make_shared<Sphere>(Point3( 0.f, -100.5f, -1.f), 100.0f, material_ground));
    // worldObjects.add(std::make_shared<Sphere>(Point3( 0.f,    0.0f, -1.f),   0.5f, material_center));
    // worldObjects.add(std::make_shared<Sphere>(Point3(-1.f,    0.0f, -1.f),   0.5f, material_left));
    // worldObjects.add(std::make_shared<Sphere>(Point3(-1.f,    0.0f, -1.f),   -0.4f, material_left));
    // worldObjects.add(std::make_shared<Sphere>(Point3( 1.f,    0.0f, -1.f),   0.5f, material_right));

    // Camera
    Camera camera(LOOK_FROM, LOOK_AT, VIEW_UP, VERTICAL_FOV_DEG, ASPECT_RATIO);
    
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
    
    if(stbi_write_png(OUT_FILENAME, IMAGE_WIDTH, IMAGE_HEIGHT, 3, imagePixels.data(), 0))
        std::cout << "Image written to " << OUT_FILENAME << std::endl;
    else
        std::cout << "Failed to write image to " << OUT_FILENAME << std::endl;

}