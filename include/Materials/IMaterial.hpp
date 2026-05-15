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

    /// Combine direct lighting with recursive ray tracing (\p traceRay).
    virtual Color shade(
        const Ray &r_in,
        const Math::Vector3D &point,
        const Math::Vector3D &normal,
        bool frontFace,
        const Color &directLighting,
        const std::function<Color(const Ray &)> &traceRay
    ) const = 0;
};

}
