/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Rotation — Euler angles in degrees (same Rx→Ry→Rz order as Camera)
*/

#pragma once

#include "Transformation/ITransformation.hpp"

namespace RayTracer {

class Rotation : public ITransformation {
public:
    explicit Rotation(const Math::Vector3D &eulerDegrees);

    Ray transformRayWorldToLocal(const Ray &worldRay) const override;
    Math::Vector3D transformPointLocalToWorld(const Math::Vector3D &localPoint) const override;
    Math::Vector3D transformNormalLocalToWorld(const Math::Vector3D &localNormal) const override;

    const Math::Vector3D &eulerDegrees() const;

    /// Reusable by \ref Camera (forward: local → world orientation of a direction).
    static Math::Vector3D rotateForward(const Math::Vector3D &v, const Math::Vector3D &eulerDegrees);
    static Math::Vector3D rotateInverse(const Math::Vector3D &v, const Math::Vector3D &eulerDegrees);

private:
    Math::Vector3D _eulerDegrees;
};

}
