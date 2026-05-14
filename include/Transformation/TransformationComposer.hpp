/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** TransformationComposer — rigid body: world p = R * p_local + T (Decorator support)
*/

#pragma once

#include "Math/Ray.hpp"
#include "Math/Vector3D.hpp"
#include "Transformation/Translation.hpp"
#include "Transformation/Rotation.hpp"

namespace RayTracer {

/// Composes \ref Translation then \ref Rotation for the rigid map
/// \(\mathbf{p}_w = R\,\mathbf{p}_l + \mathbf{T}\).
class TransformationComposer {
public:
    TransformationComposer(const Math::Vector3D &translation, const Math::Vector3D &rotationEulerDeg);

    Ray worldToLocalRay(const Ray &worldRay) const;
    Math::Vector3D localToWorldPoint(const Math::Vector3D &localPoint) const;
    Math::Vector3D localToWorldNormal(const Math::Vector3D &localNormal) const;

    bool isIdentity() const;

private:
    Translation _translation;
    Rotation _rotation;
};

}
