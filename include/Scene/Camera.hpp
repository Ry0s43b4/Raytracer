/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Camera
*/

#pragma once

#include "Math/Ray.hpp"
#include "Math/Vector3D.hpp"

namespace RayTracer {

class Camera {
public:
    Camera();
    Camera(
        int width,
        int height,
        const Math::Vector3D &position,
        const Math::Vector3D &rotation,
        double fov
    );

    int width() const;
    int height() const;
    double fov() const;
    const Math::Vector3D &position() const;
    const Math::Vector3D &rotation() const;

    Ray generateRay(int x, int y) const;

private:
    int _width;
    int _height;
    Math::Vector3D _position;
    Math::Vector3D _rotation;
    double _fov;

    Math::Vector3D rotateDirection(const Math::Vector3D &direction) const;
};

}
