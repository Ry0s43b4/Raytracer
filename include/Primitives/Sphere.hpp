/*
** EPITECH PROJECT, 2026
** G-OOP-400-PAR-4-1-raytracer-22
** File description:
** Sphere
*/

#pragma once
#include "Primitives/IPrimitive.hpp"
#include "Math/Point3D.hpp"
#include "Core/Color.hpp"

class Sphere : public IPrimitive {
    public:
        Sphere() = default;
        Sphere(Math::Point3D center, double radius, RayTracer::Color color) : center(center), radius(radius), color(color) {}
        RayTracer::Intersection Intersect(RayTracer::Ray r, RayTracer::Intersection intersection) override;
    private:
        Math::Point3D center;
        double radius;
        RayTracer::Color color;
};
