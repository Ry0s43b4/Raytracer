/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Intersection
*/

#pragma once

#include <memory>

#include "Math/Vector3D.hpp"
#include "Core/Color.hpp"
#include "Materials/IMaterial.hpp"

namespace RayTracer {

class Intersection {
public:
    Intersection();
    Intersection(
        bool hit,
        double distance,
        const Math::Vector3D &point,
        const Math::Vector3D &normal,
        const Color &color,
        const std::shared_ptr<IMaterial> &material = nullptr
    );

    bool hasHit() const;
    double distance() const;
    const Math::Vector3D &point() const;
    const Math::Vector3D &normal() const;
    const Color &color() const;
    const std::shared_ptr<IMaterial> &material() const;

    void setHit(bool hit);
    void setDistance(double distance);
    void setPoint(const Math::Vector3D &point);
    void setNormal(const Math::Vector3D &normal);
    void setColor(const Color &color);
    void setMaterial(const std::shared_ptr<IMaterial> &material);

    /// Shirley convention: incident ray and geometric outward \ref normal().
    bool frontFace(const Ray &r_in) const;

private:
    bool _hit;
    double _distance;
    Math::Vector3D _point;
    Math::Vector3D _normal;
    Color _color;
    std::shared_ptr<IMaterial> _material;
};

}
