/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Translation
*/

#pragma once

#include "Transformation/ITransformation.hpp"

namespace RayTracer {

class Translation : public ITransformation {
public:
    explicit Translation(const Math::Vector3D &offset);

    Ray transformRayWorldToLocal(const Ray &worldRay) const override;
    Math::Vector3D transformPointLocalToWorld(const Math::Vector3D &localPoint) const override;
    Math::Vector3D transformNormalLocalToWorld(const Math::Vector3D &localNormal) const override;

    const Math::Vector3D &offset() const;

private:
    Math::Vector3D _offset;
};

}
