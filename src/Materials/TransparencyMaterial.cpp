/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** TransparencyMaterial
*/

#include "Materials/TransparencyMaterial.hpp"

namespace RayTracer {

namespace {
constexpr double kEpsilon = 1e-3;
}

TransparencyMaterial::TransparencyMaterial(double transmission)
    : _transmission(transmission)
{
}

Color TransparencyMaterial::shade(
    const Ray &r_in,
    const Math::Vector3D &point,
    const Math::Vector3D &normal,
    bool /* frontFace */,
    const Color &directLighting,
    const std::function<Color(const Ray &)> &traceRay
) const
{
    Math::Vector3D dir = r_in.direction().normalized();
    Math::Vector3D offset = point + dir * kEpsilon + normal * (kEpsilon * 0.5);
    Color through = traceRay(Ray(offset, dir));

    return Color::blend(directLighting, through, _transmission);
}

}
