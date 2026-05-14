/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** AmbientLight
*/

#include <memory>
#include <vector>
#include "Lights/AmbientLight.hpp"
#include "Primitives/IPrimitive.hpp"

namespace RayTracer {

AmbientLight::AmbientLight(double intensity)
    : _intensity(intensity)
{
}

Color AmbientLight::computeLight(
    const Intersection &intersection,
    const Math::Vector3D &/*viewDir*/,
    const std::vector<std::unique_ptr<IPrimitive>> &/*primitives*/
) const
{
    const Color &c = intersection.color();

    return Color(
        static_cast<int>(c.r * _intensity),
        static_cast<int>(c.g * _intensity),
        static_cast<int>(c.b * _intensity)
    );
}

}
