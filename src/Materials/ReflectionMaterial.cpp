/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ReflectionMaterial — ideal curved mirror (local specular law on the tangent plane)
*/

#include "Materials/ReflectionMaterial.hpp"
#include "Materials/MaterialUtils.hpp"

namespace RayTracer {

namespace {
constexpr double kEpsilon = 1e-3;
}

ReflectionMaterial::ReflectionMaterial(const Color &albedo)
    : _albedo(albedo)
{
}

Color ReflectionMaterial::shade(
    const Ray &r_in,
    const Math::Vector3D &point,
    const Math::Vector3D &normal,
    bool /* frontFace */,
    const Color &/* directLighting */,
    const std::function<Color(const Ray &)> &traceRay
) const
{
    // Sphere: normal is radial outward → each surface point has a different tangent
    // plane; reflect() is the physically correct local mirror law (angle in = out).
    const Math::Vector3D n = normal.normalized();
    const Math::Vector3D reflected = reflect(r_in.direction(), n).normalized();
    const Math::Vector3D origin = point + reflected * kEpsilon;

    return Color::multiply(_albedo, traceRay(Ray(origin, reflected)));
}

const Color &ReflectionMaterial::albedo() const
{
    return _albedo;
}

}
