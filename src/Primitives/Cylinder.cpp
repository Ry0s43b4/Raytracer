/*
** EPITECH PROJECT, 2026
** G-OOP-400-PAR-4-1-raytracer-22
** File description:
** Cylinder
*/

#include "Primitives/Cylinder.hpp"

namespace RayTracer {

    Cylinder::Cylinder(
        const Math::Vector3D &center,
        const Math::Vector3D &cylinderAxis,
        double radius,
        double maximum,
        const Color &color
    )
    : _center(center), _cylinderAxis(cylinderAxis), _radius(radius), _maximum(maximum), _color(color)
    {
    }
    
    Intersection Cylinder::intersect(const Ray &ray) const
    {
        Math::Vector3D x = ray.origin() - _center;
        double a = ray.direction().dot(ray.direction()) - (ray.direction().dot(_cylinderAxis))^2;
        double b = 2 * ray.direction().dot(x) - (ray.direction().dot(_cylinderAxis) * x.dot(_cylinderAxis));
        double c = x.dot(x) - x.dot(_cylinderAxis)^2 - _radius * _radius;
    }
}