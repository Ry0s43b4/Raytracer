/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** RefractionMaterial — dielectric (Snell + Fresnel blend)
*/

#pragma once

#include "Materials/IMaterial.hpp"

namespace RayTracer {

class RefractionMaterial : public IMaterial {
public:
    /// \p ior is relative to air (e.g. 1.5 for glass).
    RefractionMaterial(const Color &tint, double ior);

    Color shade(
        const Ray &r_in,
        const Math::Vector3D &point,
        const Math::Vector3D &normal,
        bool frontFace,
        const Color &directLighting,
        const std::function<Color(const Ray &)> &traceRay
    ) const override;

private:
    Color _tint;
    double _ior;
};

}
