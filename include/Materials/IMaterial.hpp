/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** IMaterial — optical response at a shaded surface point
*/

#pragma once

#include <functional>

#include "Core/Color.hpp"
#include "Math/Ray.hpp"
#include "Math/Vector3D.hpp"

namespace RayTracer {

class IMaterial {
public:
    virtual ~IMaterial() = default;

    virtual Color shade(
        const Ray &r_in,
        const Math::Vector3D &point,
        const Math::Vector3D &normal,
        bool frontFace,
        const Color &directLighting,
        const std::function<Color(const Ray &)> &traceRay
    ) const = 0;

    virtual bool needsSpecular() const { return false; }

    virtual double shininess() const { return 0.0; }

    virtual double specularStrength() const { return 0.0; }
};

}
