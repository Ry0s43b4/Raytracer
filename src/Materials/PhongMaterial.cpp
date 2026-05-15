/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** PhongMaterial
*/

#include "Materials/PhongMaterial.hpp"

namespace RayTracer {

PhongMaterial::PhongMaterial(double shininess, double specularStrength)
    : _shininess(shininess), _specularStrength(specularStrength)
{
}

Color PhongMaterial::shade(
    const Ray &/*r_in*/,
    const Math::Vector3D &/*point*/,
    const Math::Vector3D &/*normal*/,
    bool /*frontFace*/,
    const Color &directLighting,
    const std::function<Color(const Ray &)> &/*traceRay*/
) const
{
    return directLighting;
}

}
