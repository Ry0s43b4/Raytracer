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
        const Math::Vector3D &axis,
        double radius,
        double distance,
        const Color &color
    )
    : _center(center), _ellipsoidAxis(axis.normalized()), _radius(radius), _distance(distance), _color(color)
    {
    }
    
    Intersection Ellipsoid::intersect(const Ray &ray) const
    {
        
    }
}