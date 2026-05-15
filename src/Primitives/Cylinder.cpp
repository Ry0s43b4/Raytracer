/*
** EPITECH PROJECT, 2026
** G-OOP-400-PAR-4-1-raytracer-22
** File description:
** Cylinder
*/

#include <cmath>
#include <limits>

#include "Primitives/Cylinder.hpp"

namespace RayTracer {

Cylinder::Cylinder(
    const Math::Vector3D &center,
    const Math::Vector3D &cylinderAxis,
    double radius,
    const Color &color,
    const std::shared_ptr<IMaterial> &material
)
    : _center(center),
      _cylinderAxis(cylinderAxis.normalized()),
      _radius(radius),
      _color(color),
      _material(material)
{
}

Intersection Cylinder::intersect(const Ray &ray) const
{
    Math::Vector3D x = ray.origin() - _center;

    double a = ray.direction().dot(ray.direction())
        - std::pow(ray.direction().dot(_cylinderAxis), 2);
    double b = 2.0 * ray.direction().dot(x)
        - 2.0 * (ray.direction().dot(_cylinderAxis) * x.dot(_cylinderAxis));
    double c = x.dot(x) - std::pow(x.dot(_cylinderAxis), 2) - _radius * _radius;
    double discriminant = b * b - 4.0 * a * c;

    if (discriminant < 0.0)
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

    Math::Vector3D point = ray.at(distance);
    Math::Vector3D v = point - _center;
    Math::Vector3D radial = v - _cylinderAxis * v.dot(_cylinderAxis);
    double radialLenSq = radial.dot(radial);

    if (radialLenSq < 1e-18)
        return Intersection();

    Math::Vector3D normal = radial / std::sqrt(radialLenSq);

    return Intersection(true, distance, point, normal, _color, _material);
}

}
