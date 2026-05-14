/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Translation
*/

#include "Transformation/Translation.hpp"

namespace RayTracer {

Translation::Translation(const Math::Vector3D &offset)
    : _offset(offset)
{
}

Ray Translation::transformRayWorldToLocal(const Ray &worldRay) const
{
    return Ray(worldRay.origin() - _offset, worldRay.direction());
}

Math::Vector3D Translation::transformPointLocalToWorld(const Math::Vector3D &localPoint) const
{
    return localPoint + _offset;
}

Math::Vector3D Translation::transformNormalLocalToWorld(const Math::Vector3D &localNormal) const
{
    return localNormal;
}

const Math::Vector3D &Translation::offset() const
{
    return _offset;
}

}
