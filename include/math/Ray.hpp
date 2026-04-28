/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Ray
*/

#pragma once

#include "math/Vector3D.hpp"

namespace RayTracer {

class Ray {
public:
    Ray(const Vector3D &origin, const Vector3D &direction);

    const Vector3D &origin() const;
    const Vector3D &direction() const;

    Vector3D at(double t) const;

private:
    Vector3D _origin;
    Vector3D _direction;
};

}
