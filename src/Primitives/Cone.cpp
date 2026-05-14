/*
** EPITECH PROJECT, 2026
** G-OOP-400-PAR-4-1-raytracer-22
** File description:
** Cone
*/

#include "Primitives/Cone.hpp"

namespace RayTracer {

    Cone::Cone(
        const Math::Vector3D &vertex,
        const Math::Vector3D &axis,
        double tangent,
        double maximum,
        double minimum,
        const Color &color
    )
    : _vertex(vertex), _axis(axis.normalized()), _tangent(tangent), _maximum(maximum), _minimum(minimum), _color(color)
    {
    }
    
    Intersection Cone::intersect(const Ray &ray) const
    {
        Math::Vector3D x = ray.origin() - _vertex;

        double a = ray.direction().dot(ray.direction()) - (1 + _tangent * _tangent) * ray.direction().dot(_axis) * ray.direction().dot(_axis);
        double b = 2 * (ray.direction().dot(x) - (1 + _tangent * _tangent) * ray.direction().dot(_axis) * x.dot(_axis));
        double c = x.dot(x) - (1 + _tangent * _tangent) * x.dot(_axis) * x.dot(_axis);

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
        double m = (point - _vertex).dot(_axis);
        Math::Vector3D normal = (point - _vertex - _axis * (1 +  _tangent * _tangent) * m).normalized();
        if (m < _minimum || m > _maximum)
            return Intersection();
        return Intersection(true, distance, point, normal, _color);
    }
}