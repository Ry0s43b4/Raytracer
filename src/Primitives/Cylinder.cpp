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
        
    }
}