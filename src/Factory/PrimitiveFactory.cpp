/*
** EPITECH PROJECT, 2026
** G-OOP-400-PAR-4-1-raytracer-22
** File description:
** PrimitiveFactory
*/

#include "Factory/PrimitiveFactory.hpp"
#include "Core/RaytracerError.hpp"

std::unique_ptr<IPrimitive> PrimitiveFactory::Create(std::string type, Math::Point3D center, double radius, RayTracer::Color color)
{
    if (type == "sphere") {
            return std::make_unique<Sphere>(center, radius, color);
        }
    // if (type == "plane") {
    //     return std::make_unique<Plane>(/* AJOUTER LES INFO POUR CREE LE PLAN*/);
    // }
    throw RayTracer::RaytracerError("PrimitiveFactory: unknow type: " + type + "\n");
}
