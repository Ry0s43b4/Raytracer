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
    const Color &color,
    const std::shared_ptr<IMaterial> &material
)
    : _normal(normal.normalized()), _position(position), _color(color), _material(material)
{
}

Intersection Plane::intersect(const Ray &ray) const
{
    double denom = _normal.dot(ray.direction());
    double t;
    Math::Vector3D point;

    if (std::fabs(denom) < 1e-6)
        return Intersection();

    t = (_position - _normal.dot(ray.origin())) / denom;

    if (t < 0.001)
        return Intersection();

    point = ray.at(t);
    return Intersection(true, t, point, _normal, _color, _material);
}

}
