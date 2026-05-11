/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Plane
*/

#include <cmath>
#include "Primitives/Plane.hpp"

namespace RayTracer {

Plane::Plane(
    const Math::Vector3D &normal,
    double position,
    const Color &color
)
    : _normal(normal.normalized()), _position(position), _color(color)
{
}

Intersection Plane::intersect(const Ray &ray) const
{
    double denom = _normal.dot(ray.direction());
    double t;
    Math::Vector3D point;
    Math::Vector3D normal;

    if (std::fabs(denom) < 1e-6)
        return Intersection();

    t = (_position - _normal.dot(ray.origin())) / denom;

    if (t < 0.001)
        return Intersection();

    point = ray.at(t);
    normal = (denom < 0) ? _normal : _normal * -1.0;
    return Intersection(true, t, point, normal, _color);
}

}
