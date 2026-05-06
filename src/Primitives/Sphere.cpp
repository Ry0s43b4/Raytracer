/*
** EPITECH PROJECT, 2026
** G-OOP-400-PAR-4-1-raytracer-22
** File description:
** Sphere
*/

#include "Primitives/Sphere.hpp"

RayTracer::Intersection Sphere::intersect(RayTracer::Ray r)
{
    RayTracer::Intersection intersection;
    Math::Vector3D oc = r.origin() - center;
    double a = r.direction().dot(r.direction());
    double b = 2.0 * oc.dot(r.direction());
    double c = oc.dot(oc) - radius * radius;
    double discriminant = b * b - 4 * a * c;
    float distance;

    if (discriminant < 0)
        return intersection;
    distance = (-b - std::sqrt(discriminant)) / (2.0 * a);
    if (distance <= 0.001) {
        distance = (-b + std::sqrt(discriminant)) / (2.0 * a);
        if (distance <= 0.001) {
            return intersection;
        }
    }
    return RayTracer::Intersection(true, distance, r.at(distance), (r.at(distance) - center).normalized(), color);
}