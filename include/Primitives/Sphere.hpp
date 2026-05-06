/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Sphere
*/

#pragma once

#include "Primitives/IPrimitive.hpp"
#include "Math/Vector3D.hpp"
#include "Core/Color.hpp"

namespace RayTracer {

class Sphere : public IPrimitive {
public:
    Sphere(
        const Math::Vector3D &center,
        double radius,
        const Color &color
    );

    Intersection intersect(const Ray &ray) const override;

private:
    Math::Vector3D _center;
    double _radius;
    Color _color;
};

}