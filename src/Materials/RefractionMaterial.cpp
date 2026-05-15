/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** RefractionMaterial — solid homogeneous sphere: Snell at each curved interface
** (local tangent plane = same formulas as RTW / Shirley dielectric), two-surface path
** handled by path tracing recursion.
*/

#include <cmath>

#include "Materials/RefractionMaterial.hpp"
#include "Materials/MaterialUtils.hpp"

namespace RayTracer {

namespace {
constexpr double kEpsilon = 1e-3;
}

RefractionMaterial::RefractionMaterial(const Color &tint, double ior)
    : _tint(tint), _ior(ior)
{
}

Color RefractionMaterial::shade(
    const Ray &r_in,
    const Math::Vector3D &point,
    const Math::Vector3D &normal,
    bool frontFace,
    const Color &/* directLighting */,
    const std::function<Color(const Ray &)> &traceRay
) const
{
    const Math::Vector3D outward = normal.normalized();
    const Math::Vector3D unit_dir = r_in.direction().normalized();

    // ηᵢ / ηₜ : air→glass or glass→air (same convention as Ray Tracing in One Weekend).
    const double etai_over_etat = frontFace ? (1.0 / _ior) : _ior;

    // refract() expects dot(incident, n_snell) < 0 (Shirley); geometric normal is always
    // outward on the sphere, so flip when the ray is inside the body (exit refraction).
    const Math::Vector3D n_snell = outwardToSnellNormal(unit_dir, outward);

    const double cos_theta = std::min(1.0, std::max(-1.0, -unit_dir.dot(n_snell)));
    const double sin_theta = std::sqrt(std::max(0.0, 1.0 - cos_theta * cos_theta));
    const bool cannot_refract = etai_over_etat * sin_theta > 1.0;

    // Fresnel reflection uses the physical outward normal (curved interface).
    const Math::Vector3D reflect_dir = reflect(unit_dir, outward).normalized();

    Math::Vector3D refract_raw;
    const bool ok = refract(unit_dir, n_snell, etai_over_etat, refract_raw);
    const Math::Vector3D refract_dir = ok ? refract_raw.normalized() : reflect_dir;

    if (cannot_refract || !ok) {
        const Math::Vector3D o = point + reflect_dir * kEpsilon;

        return Color::multiply(_tint, traceRay(Ray(o, reflect_dir)));
    }

    const double reflect_prob = schlick(cos_theta, etai_over_etat);
    const Math::Vector3D o_reflect = point + reflect_dir * kEpsilon;
    const Math::Vector3D o_refract = point + refract_dir * kEpsilon;

    const Color reflected = Color::multiply(_tint, traceRay(Ray(o_reflect, reflect_dir)));
    const Color refracted = Color::multiply(_tint, traceRay(Ray(o_refract, refract_dir)));

    return Color::add(
        Color::scale(reflected, reflect_prob),
        Color::scale(refracted, 1.0 - reflect_prob)
    );
}

}
