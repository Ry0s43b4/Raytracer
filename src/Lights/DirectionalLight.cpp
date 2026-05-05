/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** DirectionalLight
*/

#include <algorithm>
#include "Lights/DirectionalLight.hpp"

namespace RayTracer {

DirectionalLight::DirectionalLight(const Math::Vector3D &direction, double intensity)
    : _direction(direction.normalized()), _intensity(intensity)
{
}

Color DirectionalLight::computeLight(
    const Intersection &intersection,
    const Math::Vector3D &/*viewDir*/
) const
{
    Math::Vector3D toLight = _direction * -1.0;
    double diff = std::max(0.0, intersection.normal().dot(toLight));

    double factor = diff * _intensity;
    const Color &c = intersection.color();

    return Color(
        static_cast<int>(c.r * factor),
        static_cast<int>(c.g * factor),
        static_cast<int>(c.b * factor)
    );
}

}
