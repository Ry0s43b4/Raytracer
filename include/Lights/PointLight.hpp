/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** PointLight
*/

#pragma once

#include "Lights/ILight.hpp"

namespace RayTracer {

class PointLight : public ILight {
public:
    PointLight(const Math::Vector3D &position, double intensity);

    Color computeLight(
        const Intersection &intersection,
        const Math::Vector3D &viewDir,
        const Ray &eyeRay,
        const std::vector<std::unique_ptr<IPrimitive>> &primitives
    ) const override;

private:
    Math::Vector3D _position;
    double _intensity;
};

}
