/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Camera
*/

#include <cmath>

#include "Scene/Camera.hpp"
#include "Transformation/Rotation.hpp"

namespace {
constexpr double PI = 3.14159265358979323846;

double toRadians(double degrees)
{
    return degrees * PI / 180.0;
}
}

namespace RayTracer {

Camera::Camera()
    : _width(1),
    _height(1),
    _position(0.0, 0.0, 0.0),
    _rotation(0.0, 0.0, 0.0),
    _fov(60.0)
{
}

Camera::Camera(
    int width,
    int height,
    const Math::Vector3D &position,
    const Math::Vector3D &rotation,
    double fov
)
    : _width(width),
    _height(height),
    _position(position),
    _rotation(rotation),
    _fov(fov)
{
}

int Camera::width() const
{
    return _width;
}

int Camera::height() const
{
    return _height;
}

double Camera::fov() const
{
    return _fov;
}

const Math::Vector3D &Camera::position() const
{
    return _position;
}

const Math::Vector3D &Camera::rotation() const
{
    return _rotation;
}

Ray Camera::generateRay(int x, int y) const
{
    const double px = (2.0 * (static_cast<double>(x) + 0.5) / static_cast<double>(_width) - 1.0);
    const double py = (1.0 - 2.0 * (static_cast<double>(y) + 0.5) / static_cast<double>(_height));
    const double aspect = static_cast<double>(_width) / static_cast<double>(_height);
    const double fovScale = std::tan(toRadians(_fov) / 2.0);

    Math::Vector3D direction(
        px * aspect * fovScale,
        py * fovScale,
        1.0
    );

    return Ray(_position, rotateDirection(direction));
}

Math::Vector3D Camera::rotateDirection(const Math::Vector3D &direction) const
{
    return Rotation::rotateForward(direction, _rotation).normalized();
}

}
