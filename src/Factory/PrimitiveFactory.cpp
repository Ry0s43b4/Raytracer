/*
** EPITECH PROJECT, 2026
** G-OOP-400-PAR-4-1-raytracer-22
** File description:
** PrimitiveFactory
*/

#include "../../include/Factory/PrimitiveFactory.hpp"

std::unique_ptr<IPrimitive> PrimitiveFactory::Create(std::string type /* et ajouter les info des parametre utiliser*/)
{
    if (type == "sphere") {
            return std::make_unique<Sphere>(/* AJOUTER LES INFO POUR CREE LA SPHERE*/);
        }
    if (type == "plane") {
        return std::make_unique<Plane>(/* AJOUTER LES INFO POUR CREE LE PLAN*/);
    }
    return nullptr;
}
