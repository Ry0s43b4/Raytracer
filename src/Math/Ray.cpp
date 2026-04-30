/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Ray
*/

#include "math/Ray.hpp"

namespace RayTracer {

Ray::Ray(const Math::Vector3D &origin, const Math::Vector3D &direction)
    : _origin(origin), _direction(direction.normalized())
{
}

const Math::Vector3D &Ray::origin() const
{
    return _origin;
}

const Math::Vector3D &Ray::direction() const
{
    return _direction;
}

Math::Vector3D Ray::at(double t) const
{
    return _origin + _direction * t;
}

}
