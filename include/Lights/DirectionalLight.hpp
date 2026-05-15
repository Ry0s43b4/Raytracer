/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** DirectionalLight
*/

#pragma once

#include "Lights/ILight.hpp"

namespace RayTracer {

class DirectionalLight : public ILight {
public:
    DirectionalLight(const Math::Vector3D &direction, double intensity);

    Color computeLight(
        const Intersection &intersection,
        const Math::Vector3D &viewDir,
        const Ray &eyeRay,
        const std::vector<std::unique_ptr<IPrimitive>> &primitives
    ) const override;

private:
    Math::Vector3D _direction;
    double _intensity;
};

}
