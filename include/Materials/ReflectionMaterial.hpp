/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ReflectionMaterial — specular / mirror bounce
*/

#pragma once

#include "Materials/IMaterial.hpp"

namespace RayTracer {

class ReflectionMaterial : public IMaterial {
public:
    explicit ReflectionMaterial(const Color &albedo);

    Color shade(
        const Ray &r_in,
        const Math::Vector3D &point,
        const Math::Vector3D &normal,
        bool frontFace,
        const Color &directLighting,
        const std::function<Color(const Ray &)> &traceRay
    ) const override;

    const Color &albedo() const;

private:
    Color _albedo;
};

}
