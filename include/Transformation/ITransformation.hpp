/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** ITransformation — local / world mapping for rigid transforms
*/

#pragma once

#include "Math/Ray.hpp"
#include "Math/Vector3D.hpp"

namespace RayTracer {

/// Maps geometry defined in **local** space into **world** space (inverse used on rays).
class ITransformation {
public:
    virtual ~ITransformation() = default;

    /// World-space ray → same step toward canonical local coordinates.
    virtual Ray transformRayWorldToLocal(const Ray &worldRay) const = 0;

    /// Local point → world point (this transform only).
    virtual Math::Vector3D transformPointLocalToWorld(const Math::Vector3D &localPoint) const = 0;

    /// Local shading normal → world normal (unit length preserved if input unit).
    virtual Math::Vector3D transformNormalLocalToWorld(const Math::Vector3D &localNormal) const = 0;
};

}
