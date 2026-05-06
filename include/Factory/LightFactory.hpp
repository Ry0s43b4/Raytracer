/*
** EPITECH PROJECT, 2026
** G-OOP-400-PAR-4-1-raytracer-22
** File description:
** LightFactory
*/

#pragma once

#include <memory>
#include <string>
#include "Math/Vector3D.hpp"
#include "Math/Point3D.hpp"
#include "Lights/ILight.hpp"
#include "Lights/AmbientLight.hpp"
#include "Lights/DirectionalLight.hpp"

class LightFactory {
    public:

        LightFactory() = default;
        ~LightFactory() = default;

        std::unique_ptr<RayTracer::ILight> Create(std::string type, double intensity, Math::Vector3D direction);
};
