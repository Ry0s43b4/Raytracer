/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Plane
*/

#pragma once

#include <memory>

#include "Primitives/IPrimitive.hpp"
#include "Math/Vector3D.hpp"
#include "Core/Color.hpp"
#include "Materials/IMaterial.hpp"

namespace RayTracer {

class Plane : public IPrimitive {
public:
    Plane(
        const Math::Vector3D &normal,
        double position,
        const Color &color,
        const std::shared_ptr<IMaterial> &material = nullptr
    );

    Intersection intersect(const Ray &ray) const override;

private:
    Math::Vector3D _normal;
    double _position;
    Color _color;
    std::shared_ptr<IMaterial> _material;
};

}
