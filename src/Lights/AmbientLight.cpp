/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** AmbientLight
*/

#include "Lights/AmbientLight.hpp"

namespace RayTracer {

AmbientLight::AmbientLight(double intensity)
    : _intensity(intensity)
{
}

Color AmbientLight::computeLight(
    const Intersection &intersection,
    const Math::Vector3D &/*viewDir*/
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
