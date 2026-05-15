/*
** EPITECH PROJECT, 2026
** G-OOP-400-PAR-4-1-raytracer-22
** File description:
** Ellipsoid
*/

#pragma once

#include <memory>

#include "Primitives/IPrimitive.hpp"
#include "Math/Vector3D.hpp"
#include "Core/Color.hpp"
#include "Materials/IMaterial.hpp"

namespace RayTracer {

class Ellipsoid : public IPrimitive {
public:
    Ellipsoid(
        const Math::Vector3D &center,
        const Math::Vector3D &ellipsoidAxis,
        double radius,
        double distance,
        const Color &color,
        const std::shared_ptr<IMaterial> &material = nullptr
    );

    Intersection intersect(const Ray &ray) const override;

private:
    Math::Vector3D _center;
    Math::Vector3D _ellipsoidAxis;
    double _radius;
    double _distance;
    Color _color;
    std::shared_ptr<IMaterial> _material;
};

}