/*
** EPITECH PROJECT, 2026
** G-OOP-400-PAR-4-1-raytracer-22
** File description:
** Plane
*/

#include "Primitives/Plane.hpp"

RayTracer::Intersection Plane::Intersect(RayTracer::Ray r, RayTracer::Intersection intersection)
{
    double denom;
    double distance;
    Math::Vector3D p0l0;

    denom = normal.dot(r.direction());
    if (std::abs(denom) < 0.0001f)
        return RayTracer::Intersection();
    p0l0 = point - r.origin();
    distance = p0l0.dot(normal) / denom;

    if (distance < 0.001f)
        return RayTracer::Intersection();
    return RayTracer::Intersection(true, distance, r.at(distance), normal, color);

}