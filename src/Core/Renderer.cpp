/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Renderer
*/

#include <limits>

#include "Core/Renderer.hpp"
#include "Math/Ray.hpp"
#include "Materials/IMaterial.hpp"

namespace RayTracer {

Image Renderer::render(const Scene &scene) const
{
    const Camera &camera = scene.camera();
    Image image(camera.width(), camera.height());

    for (int y = 0; y < camera.height(); y++) {
        for (int x = 0; x < camera.width(); x++) {
            Ray ray = camera.generateRay(x, y);

            image.setPixel(x, y, traceRay(ray, scene, kMaxTraceDepth));
        }
    }

    return image;
}

Intersection Renderer::castRay(const Ray &ray, const Scene &scene, double tMin) const
{
    Intersection closest;
    double minDistance = std::numeric_limits<double>::infinity();

    for (const auto &primitive : scene.primitives()) {
        Intersection hit = primitive->intersect(ray);

        if (hit.hasHit() && hit.distance() >= tMin && hit.distance() < minDistance) {
            minDistance = hit.distance();
            closest = hit;
        }
    }

    return closest;
}

Color Renderer::computeDirectLighting(
    const Intersection &intersection,
    const Ray &eyeRay,
    const Scene &scene
) const
{
    Math::Vector3D viewDir = (eyeRay.origin() - intersection.point()).normalized();

    Color finalColor;

    for (const auto &light : scene.lights()) {
        Color c = light->computeLight(
            intersection, viewDir, eyeRay, scene.primitives()
        );
        finalColor.r += c.r;
        finalColor.g += c.g;
        finalColor.b += c.b;
    }

    finalColor.clamp();
    return finalColor;
}

Color Renderer::traceRay(const Ray &ray, const Scene &scene, int depth) const
{
    if (depth <= 0)
        return Color(0, 0, 0);

    const double tMin = (depth == kMaxTraceDepth) ? 0.0 : 1e-2;

    Intersection hit = castRay(ray, scene, tMin);

    if (!hit.hasHit())
        return Color(0, 0, 0);

    Color direct = computeDirectLighting(hit, ray, scene);

    if (hit.material()) {
        bool frontFace = hit.frontFace(ray);

        return hit.material()->shade(
            ray,
            hit.point(),
            hit.normal(),
            frontFace,
            direct,
            [&](const Ray &child) { return traceRay(child, scene, depth - 1); }
        );
    }

    return direct;
}

}
