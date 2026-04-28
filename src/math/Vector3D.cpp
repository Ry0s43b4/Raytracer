/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Vector3D
*/

#include "math/Vector3D.hpp"

namespace RayTracer {

Vector3D::Vector3D() : x(0), y(0), z(0) {}

Vector3D::Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}

double Vector3D::length() const
{
    return std::sqrt(x * x + y * y + z * z);
}

double Vector3D::dot(const Vector3D &other) const
{
    return x * other.x + y * other.y + z * other.z;
}

Vector3D Vector3D::normalized() const
{
    double len = length();

    if (len == 0)
        return Vector3D();
    return Vector3D(x / len, y / len, z / len);
}

Vector3D Vector3D::operator+(const Vector3D &other) const
{
    return Vector3D(x + other.x, y + other.y, z + other.z);
}

Vector3D Vector3D::operator-(const Vector3D &other) const
{
    return Vector3D(x - other.x, y - other.y, z - other.z);
}

Vector3D Vector3D::operator*(double scalar) const
{
    return Vector3D(x * scalar, y * scalar, z * scalar);
}

Vector3D Vector3D::operator/(double scalar) const
{
    return Vector3D(x / scalar, y / scalar, z / scalar);
}

}
