/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Intersection
*/

#pragma once

#include "Math/Vector3D.hpp"
#include "Core/Color.hpp"

namespace RayTracer {

class Intersection {
public:
    Intersection();
    Intersection(
        bool hit,
        double distance,
        const Math::Vector3D &point,
        const Math::Vector3D &normal,
        const Color &color
    );

    bool hasHit() const;
    double distance() const;
    const Math::Vector3D &point() const;
    const Math::Vector3D &normal() const;
    const Color &color() const;

    void setHit(bool hit);
    void setDistance(double distance);
    void setPoint(const Math::Vector3D &point);
    void setNormal(const Math::Vector3D &normal);
    void setColor(const Color &color);

private:
    bool _hit;
    double _distance;
    Math::Vector3D _point;
    Math::Vector3D _normal;
    Color _color;
};

}
