/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** PrimitiveFactory
*/

#include "Factory/PrimitiveFactory.hpp"
#include "Core/RaytracerError.hpp"

namespace RayTracer {

std::unique_ptr<IPrimitive> PrimitiveFactory::Create(
    const std::string &type,
    const Math::Vector3D &vectorParam,
    double scalarParam,
    const Color &color
)
{
    if (type == "sphere")
        return std::make_unique<Sphere>(vectorParam, scalarParam, color);

    if (type == "plane")
        return std::make_unique<Plane>(vectorParam, scalarParam, color);

    throw RaytracerError("PrimitiveFactory: unknown primitive type '" + type + "'");
}

}
