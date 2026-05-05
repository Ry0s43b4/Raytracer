/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** AmbientLight
*/

#pragma once

#include "Lights/ILight.hpp"

namespace RayTracer {

class AmbientLight : public ILight {
public:
    explicit AmbientLight(double intensity);

    Color computeLight(
        const Intersection &intersection,
        const Math::Vector3D &viewDir
    ) const override;

private:
    double _intensity;
};

}
