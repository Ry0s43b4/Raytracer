/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Renderer
*/

#include <limits>
#include "Core/Renderer.hpp"
#include "Math/Ray.hpp"

namespace RayTracer {

Image Renderer::render(const Scene &scene) const
{
    const Camera &camera = scene.camera();
    Image image(camera.width(), camera.height());

    for (int y = 0; y < camera.height(); y++) {
        for (int x = 0; x < camera.width(); x++) {
            RayTracer::Ray ray = camera.generateRay(x, y);

            Intersection closest = castRay(ray, scene);

            Color finalColor;
            if (closest.hasHit())
                finalColor = computeColor(closest, ray, scene);

            image.setPixel(x, y, finalColor);
        }
    }

    return image;
}

Intersection Renderer::castRay(const RayTracer::Ray &ray, const Scene &scene) const
{
    Intersection closest;
    double minDistance = std::numeric_limits<double>::infinity();

    for (const auto &primitive : scene.primitives()) {
        Intersection hit = primitive->intersect(ray);

        if (hit.hasHit() && hit.distance() < minDistance) {
            minDistance = hit.distance();
            closest = hit;
        }
    }

    return closest;
}

Color Renderer::computeColor(
    const Intersection &intersection,
    const RayTracer::Ray &ray,
    const Scene &scene
) const
{
    Math::Vector3D viewDir = (ray.origin() - intersection.point()).normalized();

    Color finalColor;

    for (const auto &light : scene.lights()) {
        Color c = light->computeLight(intersection, viewDir);
        finalColor.r += c.r;
        finalColor.g += c.g;
        finalColor.b += c.b;
    }

    finalColor.clamp();
    return finalColor;
}

}
