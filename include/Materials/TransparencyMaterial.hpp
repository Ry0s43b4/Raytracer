/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** TransparencyMaterial — see-through surface (alpha blend with straight-through ray)
*/

#pragma once

#include "Materials/IMaterial.hpp"

namespace RayTracer {

class TransparencyMaterial : public IMaterial {
public:
    /// \p transmission in [0, 1]: 0 opaque (only direct), 1 fully transparent (only through-ray).
    explicit TransparencyMaterial(double transmission);

    Color shade(
        const Ray &r_in,
        const Math::Vector3D &point,
        const Math::Vector3D &normal,
        bool frontFace,
        const Color &directLighting,
        const std::function<Color(const Ray &)> &traceRay
    ) const override;

private:
    double _transmission;
};

}
