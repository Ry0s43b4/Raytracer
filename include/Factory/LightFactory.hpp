/*
** EPITECH PROJECT, 2026
** G-OOP-400-PAR-4-1-raytracer-22
** File description:
** LightFactory
*/

#pragma once

#include <memory>
#include <string>
#include "../math/Vector3D.hpp"
#include "../math/Point3D.hpp"
#include "../lights/ILight.hpp"
#include "../lights/AmbientLight.hpp"
#include "../lights/DirectionalLight.hpp"

class LightFactory {
    public:

        LightFactory() = default;
        ~LightFactory() = default;

        std::unique_ptr<ILight> Create(std::string type /* et ajouter les info des parametre utiliser*/);
};
