/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** DirectionalLight
*/

#include <algorithm>
#include <memory>
#include <vector>

#include "Lights/DirectionalLight.hpp"
#include "Primitives/IPrimitive.hpp"
#include "Math/Ray.hpp"

namespace RayTracer {

static constexpr double SHADOW_EPSILON = 1e-4;

DirectionalLight::DirectionalLight(const Math::Vector3D &direction, double intensity)
    : _direction(direction.normalized()), _intensity(intensity)
{
}

Color DirectionalLight::computeLight(
    const Intersection &intersection,
    const Math::Vector3D &/*viewDir*/,
    const Ray &/*eyeRay*/,
    const std::vector<std::unique_ptr<IPrimitive>> &primitives
) const
{
    Math::Vector3D toLight = (_direction * -1.0).normalized();
    double diff = std::max(0.0, intersection.normal().dot(toLight));

    if (diff <= 0.0)
        return Color(0, 0, 0);


    Math::Vector3D shadowOrigin = intersection.point() + intersection.normal() * SHADOW_EPSILON;
    Ray shadowRay(shadowOrigin, toLight);

    for (const auto &primitive : primitives) {
        Intersection shadowHit = primitive->intersect(shadowRay);
        if (shadowHit.hasHit() && shadowHit.distance() > SHADOW_EPSILON)
            return Color(0, 0, 0);
    }

    double factor = diff * _intensity;
    const Color &c = intersection.color();

    return Color(
        static_cast<int>(c.r * factor),
        static_cast<int>(c.g * factor),
        static_cast<int>(c.b * factor)
    );
}

}
