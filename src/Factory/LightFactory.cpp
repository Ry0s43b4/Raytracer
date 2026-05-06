/*
** EPITECH PROJECT, 2026
** G-OOP-400-PAR-4-1-raytracer-22
** File description:
** LightFactory
*/

#include "Factory/LightFactory.hpp"

std::unique_ptr<RayTracer::ILight> LightFactory::Create(std::string type, double intensity, Math::Vector3D direction)
{
    if (type == "ambient") {
            return std::make_unique<RayTracer::AmbientLight>(intensity);
        }
    if (type == "directional") {
        return std::make_unique<RayTracer::DirectionalLight>(direction, intensity);
    }
}
