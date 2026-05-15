/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** DirectionalLight
*/

#include <algorithm>
#include <cmath>
#include <memory>
#include <vector>

#include "Lights/DirectionalLight.hpp"
#include "Materials/MaterialUtils.hpp"
#include "Primitives/IPrimitive.hpp"
#include "Math/Ray.hpp"

namespace RayTracer {

static constexpr double SHADOW_EPSILON = 1e-4;

DirectionalLight::DirectionalLight(const Math::Vector3D &direction, double intensity)
    : _direction(direction.normalized()), _intensity(intensity)
{
}

bool DirectionalLight::isInShadow(
    const Intersection &intersection,
    const std::vector<std::unique_ptr<IPrimitive>> &primitives
) const
{
    Math::Vector3D toLight = (_direction * -1.0).normalized();
    Math::Vector3D shadowOrigin = intersection.point() + intersection.normal() * SHADOW_EPSILON;
    Ray shadowRay(shadowOrigin, toLight);

    for (const auto &primitive : primitives) {
        Intersection shadowHit = primitive->intersect(shadowRay);
        if (shadowHit.hasHit() && shadowHit.distance() > SHADOW_EPSILON)
            return true;
    }
    return false;
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

    if (isInShadow(intersection, primitives))
        return Color(0, 0, 0);

    double factor = diff * _intensity;
    const Color &c = intersection.color();

    return Color(
        static_cast<int>(c.r * factor),
        static_cast<int>(c.g * factor),
        static_cast<int>(c.b * factor)
    );
}

Color DirectionalLight::computeSpecular(
    const Intersection &intersection,
    const Math::Vector3D &viewDir,
    double shininess,
    double specularStrength,
    const std::vector<std::unique_ptr<IPrimitive>> &primitives
) const
{
    Math::Vector3D toLight = (_direction * -1.0).normalized();

    if (intersection.normal().dot(toLight) <= 0.0)
        return Color(0, 0, 0);

    if (isInShadow(intersection, primitives))
        return Color(0, 0, 0);

    Math::Vector3D R = reflect(toLight * -1.0, intersection.normal()).normalized();
    double spec = std::pow(std::max(0.0, viewDir.dot(R)), shininess);
    double factor = spec * specularStrength * _intensity;

    return Color(
        static_cast<int>(255 * factor),
        static_cast<int>(255 * factor),
        static_cast<int>(255 * factor)
    );
}

}
