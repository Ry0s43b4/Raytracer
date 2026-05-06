/*
** EPITECH PROJECT, 2026
** G-OOP-400-PAR-4-1-raytracer-22
** File description:
** Plane
*/

#pragma once
#include "Primitives/IPrimitive.hpp"
#include "Math/Vector3D.hpp"
#include "Math/Point3D.hpp"
#include "Core/Color.hpp"

class Plane : public IPrimitive {
    public:
        Plane() = default;
        Plane(Math::Point3D point, Math::Vector3D normal) : point(point), normal(normal) {}
        RayTracer::Intersection intersect(RayTracer::Ray r) override;

    private:
        Math::Point3D point;
        Math::Vector3D normal;
        RayTracer::Color color;
};
