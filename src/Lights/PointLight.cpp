/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** PointLight
*/

#include <algorithm>
#include <cmath>
#include <memory>
#include <vector>

#include "Lights/PointLight.hpp"
#include "Primitives/IPrimitive.hpp"
#include "Math/Ray.hpp"

namespace RayTracer {

static constexpr double SHADOW_EPSILON = 1e-4;

PointLight::PointLight(const Math::Vector3D &position, double intensity)
    : _position(position), _intensity(intensity)
{
}

Color PointLight::computeLight(
    const Intersection &intersection,
    const Math::Vector3D &/*viewDir*/,
    const Ray &/*eyeRay*/,
    const std::vector<std::unique_ptr<IPrimitive>> &primitives
) const
{
    Math::Vector3D toLight = _position - intersection.point();
    double distToLight = toLight.length();

    if (distToLight < SHADOW_EPSILON)
        return Color(0, 0, 0);

    Math::Vector3D toLightDir = toLight / distToLight;
    double diff = std::max(0.0, intersection.normal().dot(toLightDir));

    if (diff <= 0.0)
        return Color(0, 0, 0);

    Math::Vector3D shadowOrigin = intersection.point() + intersection.normal() * SHADOW_EPSILON;
    Ray shadowRay(shadowOrigin, toLightDir);

    for (const auto &primitive : primitives) {
        Intersection shadowHit = primitive->intersect(shadowRay);
        if (shadowHit.hasHit()
            && shadowHit.distance() > SHADOW_EPSILON
            && shadowHit.distance() < distToLight)
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
