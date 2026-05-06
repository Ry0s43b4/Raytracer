/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Vector3D
*/

#pragma once

#include <cmath>

namespace Math {

class Vector3D {
public:
    double x;
    double y;
    double z;

    Vector3D();
    Vector3D(double x, double y, double z);

    double length() const;
    double dot(const Vector3D &other) const;
    Vector3D normalized() const;

    Vector3D operator+(const Vector3D &other) const;
    Vector3D operator-(const Vector3D &other) const;
    Vector3D operator*(double scalar) const;
    Vector3D operator/(double scalar) const;
    Vector3D Vector3D::operator-(const Point3D &other) const;
};

}
