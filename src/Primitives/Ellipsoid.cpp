/*
** EPITECH PROJECT, 2026
** G-OOP-400-PAR-4-1-raytracer-22
** File description:
** Ellipsoid
*/

#include "Ellipsoid.hpp"

namespace RayTracer {

    Ellipsoid::Ellipsoid(
        const Math::Vector3D &center,
        const Math::Vector3D &ellipsoidAxis,
        double radius,
        double distance,
        const Color &color
    )
    : _center(center), _ellipsoidAxis(ellipsoidAxis.normalized()), _radius(radius), _distance(distance), _color(color)
    {
    }
    
    Intersection Ellipsoid::intersect(const Ray &ray) const
    {
        Math::Vector3D x = ray.origin() - _center;

        double a = 4 * _radius * _radius * (ray.direction().dot(_ellipsoidAxis) * ray.direction().dot(_ellipsoidAxis));
        double b = 2 * (_radius * _radius * ray.direction().dot(x) - 2 * (ray.direction().dot(_ellipsoidAxis)) * _distance * (_radius * _radius + 2 * x.dot(_ellipsoidAxis) * _distance - _distance));
        double c = 4 * _radius * _radius * x.dot(x) - ((_radius * _radius + 2 * x.dot(_ellipsoidAxis) * _distance - _distance) * (_radius * _radius + 2 * x.dot(_ellipsoidAxis) * _distance - _distance));
        
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
        Math::Vector3D cmid = _center + _ellipsoidAxis * (_distance / 2);
        Math::Vector3D R = point - cmid;
        Math::Vector3D normal = (R - _ellipsoidAxis * (1 - (b * b) / (a * a)) * (R.dot(_ellipsoidAxis)));
        return Intersection(true, distance, point, normal.normalized(), _color);
    }
}