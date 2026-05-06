/*
** EPITECH PROJECT, 2026
** G-OOP-400-PAR-4-1-raytracer-22
** File description:
** Plane
*/

#include <cmath>
#include "Primitives/Plane.hpp"

namespace RayTracer {

Plane::Plane(
    const Math::Vector3D &point,
    const Math::Vector3D &normal,
    const Color &color
)
    : _point(point), _normal(normal.normalized()), _color(color)
{
}

Intersection Plane::intersect(const Ray &ray) const
{
    double denom;
    double distance;
    Math::Vector3D p0l0;

    denom = _normal.dot(ray.direction());
    if (std::abs(denom) < 1e-6)
        return Intersection();

    p0l0 = _point - ray.origin();
    distance = p0l0.dot(_normal) / denom;

    if (distance < 0.001)
        return Intersection();

    Math::Vector3D normal = (denom < 0) ? _normal : _normal * -1.0;

    return Intersection(true, distance, ray.at(distance), normal, _color);
}

}