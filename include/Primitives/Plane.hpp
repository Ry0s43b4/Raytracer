/*
** EPITECH PROJECT, 2026
** G-OOP-400-PAR-4-1-raytracer-22
** File description:
** Plane
*/

#pragma once
#include "Primitives/IPrimitive.hpp"
#include "Math/Vector3D.hpp"
#include "Core/Color.hpp"

namespace RayTracer {

class Plane : public IPrimitive {
public:
    Plane(
        const Math::Vector3D &point,
        const Math::Vector3D &normal,
        const Color &color
    );

    Intersection intersect(const Ray &ray) const override;

private:
    Math::Vector3D _point;
    Math::Vector3D _normal;
    Color _color;
};

}
