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
        double a = ray.direction().dot(ray.direction()) - (ray.direction().dot(_cylinderAxis))^2;
        double b = ray.direction().dot(_center.x) - (ray.direction().dot(_cylinderAxis) * _center.dot(_cylinderAxis));
        double c = _center.dot(_center) - _center.dot(_cylinderAxis)^2 - _radius * _radius;
    }
}