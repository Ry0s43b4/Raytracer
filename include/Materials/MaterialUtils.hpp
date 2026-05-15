/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** MaterialUtils — reflect / refract / Fresnel (smooth interface, local tangent plane)
*/

#pragma once

#include <algorithm>
#include <cmath>

#include "Math/Vector3D.hpp"

namespace RayTracer {

/// Specular reflection. \p in and \p normal are unit vectors; \p normal is the
/// **local** surface normal (for a sphere: radial outward). Curved-mirror appearance
/// comes from tracing many pixels, each with its own \p normal on the surface.
inline Math::Vector3D reflect(const Math::Vector3D &in, const Math::Vector3D &normal)
{
    return in - normal * (2.0 * in.dot(normal));
}

/// Snell–Descartes (vector form, Shirley / RTW). \p normal must satisfy
/// \c dot(in, normal) < 0 (incident ray lies in the half-space opposite to \p normal).
/// \p etai_over_etat is ηᵢ / ηₜ (incident IOR divided by transmitted IOR).
inline bool refract(
    const Math::Vector3D &in,
    const Math::Vector3D &normal,
    double etai_over_etat,
    Math::Vector3D &out
)
{
    double cos_theta = std::min(std::max(-in.dot(normal), -1.0), 1.0);
    Math::Vector3D r_perp = (in + normal * cos_theta) * etai_over_etat;
    double len_sq = r_perp.dot(r_perp);
    double discriminant = 1.0 - len_sq;

    if (discriminant < 0.0)
        return false;
    Math::Vector3D r_parallel = normal * (-std::sqrt(discriminant));
    out = r_perp + r_parallel;
    return true;
}

/// For a smooth boundary with geometric **outward** unit normal, return a normal
/// oriented for \ref refract (incident propagation \p wi with dot(wi, n) < 0).
inline Math::Vector3D outwardToSnellNormal(const Math::Vector3D &wi, const Math::Vector3D &outward)
{
    if (wi.dot(outward) > 0.0)
        return outward * -1.0;
    return outward;
}

/// Schlick Fresnel approximation; \p ref_idx is ηᵢ/ηₜ (same ratio as Snell).
inline double schlick(double cosine, double ref_idx)
{
    double r0 = (1.0 - ref_idx) / (1.0 + ref_idx);

    r0 = r0 * r0;
    return r0 + (1.0 - r0) * std::pow(1.0 - cosine, 5);
}

}
