/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** main
*/

#include <iostream>

#include "Math/Vector3D.hpp"
#include "Math/Ray.hpp"
#include "Core/Color.hpp"

int main(void)
{
    Math::Vector3D origin(0, 0, 0);
    Math::Vector3D direction(1, 0, 0);
    RayTracer::Ray ray(origin, direction);
    RayTracer::Color color(255, 0, 0);

    color.clamp();

    std::cout << "Raytracer core initialized." << std::endl;
    std::cout << "Ray origin: "
              << ray.origin().x << " "
              << ray.origin().y << " "
              << ray.origin().z << std::endl;

    return 0;
}
