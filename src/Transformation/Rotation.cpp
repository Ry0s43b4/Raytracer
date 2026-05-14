/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Rotation
*/

#include <cmath>

#include "Transformation/Rotation.hpp"

namespace {

constexpr double PI = 3.14159265358979323846;

double toRadians(double degrees)
{
    return degrees * PI / 180.0;
}

}

namespace RayTracer {

Rotation::Rotation(const Math::Vector3D &eulerDegrees)
    : _eulerDegrees(eulerDegrees)
{
}

const Math::Vector3D &Rotation::eulerDegrees() const
{
    return _eulerDegrees;
}

Math::Vector3D Rotation::rotateForward(const Math::Vector3D &v, const Math::Vector3D &eulerDeg)
{
    const double rx = toRadians(eulerDeg.x);
    const double ry = toRadians(eulerDeg.y);
    const double rz = toRadians(eulerDeg.z);

    Math::Vector3D rotated = v;

    rotated = Math::Vector3D(
        rotated.x,
        rotated.y * std::cos(rx) - rotated.z * std::sin(rx),
        rotated.y * std::sin(rx) + rotated.z * std::cos(rx)
    );
    rotated = Math::Vector3D(
        rotated.x * std::cos(ry) + rotated.z * std::sin(ry),
        rotated.y,
        -rotated.x * std::sin(ry) + rotated.z * std::cos(ry)
    );
    rotated = Math::Vector3D(
        rotated.x * std::cos(rz) - rotated.y * std::sin(rz),
        rotated.x * std::sin(rz) + rotated.y * std::cos(rz),
        rotated.z
    );

    return rotated;
}

Math::Vector3D Rotation::rotateInverse(const Math::Vector3D &v, const Math::Vector3D &eulerDeg)
{
    const double rx = toRadians(eulerDeg.x);
    const double ry = toRadians(eulerDeg.y);
    const double rz = toRadians(eulerDeg.z);

    Math::Vector3D rotated = v;

    rotated = Math::Vector3D(
        rotated.x * std::cos(rz) + rotated.y * std::sin(rz),
        -rotated.x * std::sin(rz) + rotated.y * std::cos(rz),
        rotated.z
    );
    rotated = Math::Vector3D(
        rotated.x * std::cos(ry) - rotated.z * std::sin(ry),
        rotated.y,
        rotated.x * std::sin(ry) + rotated.z * std::cos(ry)
    );
    rotated = Math::Vector3D(
        rotated.x,
        rotated.y * std::cos(rx) + rotated.z * std::sin(rx),
        -rotated.y * std::sin(rx) + rotated.z * std::cos(rx)
    );

    return rotated;
}

Ray Rotation::transformRayWorldToLocal(const Ray &worldRay) const
{
    const Math::Vector3D o = rotateInverse(worldRay.origin(), _eulerDegrees);
    const Math::Vector3D d = rotateInverse(worldRay.direction(), _eulerDegrees);

    return Ray(o, d);
}

Math::Vector3D Rotation::transformPointLocalToWorld(const Math::Vector3D &localPoint) const
{
    return rotateForward(localPoint, _eulerDegrees);
}

Math::Vector3D Rotation::transformNormalLocalToWorld(const Math::Vector3D &localNormal) const
{
    return rotateForward(localNormal, _eulerDegrees);
}

}
