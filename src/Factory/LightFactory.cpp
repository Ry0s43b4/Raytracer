/*
** EPITECH PROJECT, 2026
** G-OOP-400-PAR-4-1-raytracer-22
** File description:
** LightFactory
*/

#include "Factory/LightFactory.hpp"

std::unique_ptr<ILight> LightFactory::Create(std::string type, double intensity, Math::Vector3D direction)
{
    if (type == "ambient") {
            return std::make_unique<AmbientLight>(intensity);
        }
    if (type == "directional") {
        return std::make_unique<DirectionalLight>(intensity, direction);
    }
    return nullptr;
}
