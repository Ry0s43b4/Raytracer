/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Ray
*/

#pragma once

#include "Math/Vector3D.hpp"

namespace RayTracer {

class Ray {
public:
    Ray(const Math::Vector3D &origin, const Math::Vector3D &direction);

    const Math::Vector3D &origin() const;
    const Math::Vector3D &direction() const;

    Math::Vector3D at(double t) const;

private:
    Math::Vector3D _origin;
    Math::Vector3D _direction;
};

}
