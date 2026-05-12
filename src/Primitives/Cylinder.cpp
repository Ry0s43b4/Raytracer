/*
** EPITECH PROJECT, 2026
** G-OOP-400-PAR-4-1-raytracer-22
** File description:
** Cylinder
*/

#include "Primitives/Cylinder.hpp"

namespace RayTracer {

    Cylinder::Cylinder(
        const Math::Point3D &center,
        const Math::Vector3D &cylinderAxis,
        double radius,
        const Color &color
    )
    : _center(center), _cylinderAxis(cylinderAxis), _radius(radius), _color(color)
    {
    }
    
    Intersection Cylinder::intersect(const Ray &ray) const
    {
        Math::Vector3D x = ray.origin() - _center;

        double a = ray.direction().dot(ray.direction()) - (ray.direction().dot(_cylinderAxis)) * (ray.direction().dot(_cylinderAxis));
        double b = 2 * ray.direction().dot(x) - (ray.direction().dot(_cylinderAxis) * x.dot(_cylinderAxis));
        double c = x.dot(x) - x.dot(_cylinderAxis) * x.dot(_cylinderAxis) - _radius * _radius;
        double discriminant = b * b - 4 * a * c;
        
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