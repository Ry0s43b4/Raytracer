/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Sphere
*/

#pragma once

#include <memory>

#include "Primitives/IPrimitive.hpp"
#include "Math/Vector3D.hpp"
#include "Core/Color.hpp"
#include "Materials/IMaterial.hpp"

namespace RayTracer {

class Sphere : public IPrimitive {
public:
    Sphere(
        const Math::Vector3D &center,
        double radius,
        const Color &color,
        const std::shared_ptr<IMaterial> &material = nullptr
    );

    Intersection intersect(const Ray &ray) const override;

private:
    Math::Vector3D _center;
    double _radius;
    Color _color;
    std::shared_ptr<IMaterial> _material;
};

}