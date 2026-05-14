/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** TransformationComposer
*/

#include "Transformation/TransformationComposer.hpp"

namespace RayTracer {

TransformationComposer::TransformationComposer(
    const Math::Vector3D &translation,
    const Math::Vector3D &rotationEulerDeg
)
    : _translation(translation),
      _rotation(rotationEulerDeg)
{
}

Ray TransformationComposer::worldToLocalRay(const Ray &worldRay) const
{
    const Ray afterTranslation = _translation.transformRayWorldToLocal(worldRay);

    return _rotation.transformRayWorldToLocal(afterTranslation);
}

Math::Vector3D TransformationComposer::localToWorldPoint(const Math::Vector3D &localPoint) const
{
    return _translation.transformPointLocalToWorld(
        _rotation.transformPointLocalToWorld(localPoint)
    );
}

Math::Vector3D TransformationComposer::localToWorldNormal(const Math::Vector3D &localNormal) const
{
    return _rotation.transformNormalLocalToWorld(localNormal);
}

bool TransformationComposer::isIdentity() const
{
    const Math::Vector3D &t = _translation.offset();
    const Math::Vector3D &e = _rotation.eulerDegrees();

    return t.x == 0.0 && t.y == 0.0 && t.z == 0.0
        && e.x == 0.0 && e.y == 0.0 && e.z == 0.0;
}

}
