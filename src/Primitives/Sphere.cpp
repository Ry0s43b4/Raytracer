/*
** EPITECH PROJECT, 2026
** G-OOP-400-PAR-4-1-raytracer-22
** File description:
** Sphere
*/

#include <cmath>
#include <limits>
#include "Primitives/Sphere.hpp"

namespace RayTracer {

Sphere::Sphere(
    const Math::Vector3D &center,
    double radius,
    const Color &color,
    const std::shared_ptr<IMaterial> &material
)
    : _center(center), _radius(radius), _color(color), _material(material)
{
}

Intersection Sphere::intersect(const Ray &ray) const
{
    Math::Vector3D oc = ray.origin() - _center;

    double a = ray.direction().dot(ray.direction());
    double b = 2.0 * oc.dot(ray.direction());
    double c = oc.dot(oc) - _radius * _radius;
    double discriminant = b * b - 4.0 * a * c;

    if (discriminant < 0)
        return Intersection();

    double sqrtd = std::sqrt(discriminant);
    double inv2a = 1.0 / (2.0 * a);
    double t0 = (-b - sqrtd) * inv2a;
    double t1 = (-b + sqrtd) * inv2a;

    constexpr double kSurfEps = 1e-3;
    double distance = std::numeric_limits<double>::infinity();

    if (t0 > kSurfEps)
        distance = t0;
    if (t1 > kSurfEps)
        distance = std::min(distance, t1);
    if (!std::isfinite(distance))
        return Intersection();

    Math::Vector3D point  = ray.at(distance);
    Math::Vector3D normal = (point - _center).normalized();

    return Intersection(true, distance, point, normal, _color, _material);
}

}