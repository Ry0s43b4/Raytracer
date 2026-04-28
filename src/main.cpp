/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** main
*/

#include <iostream>

#include "math/Vector3D.hpp"
#include "math/Ray.hpp"
#include "core/Color.hpp"

int main(void)
{
    RayTracer::Vector3D origin(0, 0, 0);
    RayTracer::Vector3D direction(1, 0, 0);
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
