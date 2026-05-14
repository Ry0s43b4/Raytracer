/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** LightFactory
*/

#pragma once

#include <memory>
#include <string>

#include "Lights/ILight.hpp"
#include "Lights/AmbientLight.hpp"
#include "Lights/DirectionalLight.hpp"
#include "Lights/PointLight.hpp"
#include "Math/Vector3D.hpp"

namespace RayTracer {

class LightFactory {
public:
    LightFactory() = default;
    ~LightFactory() = default;

    std::unique_ptr<ILight> Create(
        const std::string &type,
        double intensity,
        const Math::Vector3D &directionOrPosition = Math::Vector3D(0, -1, 0)
    );
};

}
