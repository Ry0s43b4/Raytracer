/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Intersection
*/

#include "core/Intersection.hpp"

namespace RayTracer {

Intersection::Intersection()
    : _hit(false),
      _distance(0.0),
      _point(),
      _normal(),
      _color()
{
}

Intersection::Intersection(
    bool hit,
    double distance,
    const Math::Vector3D &point,
    const Math::Vector3D &normal,
    const Color &color
)
    : _hit(hit),
      _distance(distance),
      _point(point),
      _normal(normal),
      _color(color)
{
}

bool Intersection::hasHit() const
{
    return _hit;
}

double Intersection::distance() const
{
    return _distance;
}

const Math::Vector3D &Intersection::point() const
{
    return _point;
}

const Math::Vector3D &Intersection::normal() const
{
    return _normal;
}

const Color &Intersection::color() const
{
    return _color;
}

void Intersection::setHit(bool hit)
{
    _hit = hit;
}

void Intersection::setDistance(double distance)
{
    _distance = distance;
}

void Intersection::setPoint(const Math::Vector3D &point)
{
    _point = point;
}

void Intersection::setNormal(const Math::Vector3D &normal)
{
    _normal = normal;
}

void Intersection::setColor(const Color &color)
{
    _color = color;
}

}
