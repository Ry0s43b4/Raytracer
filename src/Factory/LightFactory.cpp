/*
** EPITECH PROJECT, 2026
** G-OOP-400-PAR-4-1-raytracer-22
** File description:
** LightFactory
*/

#include "Factory/LightFactory.hpp"

std::unique_ptr<ILight> LightFactory::Create(std::string type /* et ajouter les info des parametre utiliser*/)
{
    if (type == "ambient") {
            return std::make_unique<AmbientLight>(/* AJOUTER LES INFO POUR CREE LA SPHERE*/);
        }
    if (type == "directional") {
        return std::make_unique<DirectionalLight>(/* AJOUTER LES INFO POUR CREE LE PLAN*/);
    }
    return nullptr;
}
