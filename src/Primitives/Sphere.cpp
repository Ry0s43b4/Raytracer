/*
** EPITECH PROJECT, 2026
** G-OOP-400-PAR-4-1-raytracer-22
** File description:
** Sphere
*/

#include <cmath>
#include "Primitives/Sphere.hpp"

namespace RayTracer {

Sphere::Sphere(
    const Math::Vector3D &center,
    double radius,
    const Color &color
)
    : _center(center), _radius(radius), _color(color)
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

    double distance = (-b - std::sqrt(discriminant)) / (2.0 * a);
    if (distance <= 0.001) {
        distance = (-b + std::sqrt(discriminant)) / (2.0 * a);
        if (distance <= 0.001)
            return Intersection();
    }

    Math::Vector3D point  = ray.at(distance);
    Math::Vector3D normal = (point - _center).normalized();

    return Intersection(true, distance, point, normal, _color);
}

}