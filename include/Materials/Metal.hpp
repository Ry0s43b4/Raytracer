/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Metal — reflective surface (uses ReflectionMaterial)
*/

#pragma once

#include "Materials/ReflectionMaterial.hpp"

namespace RayTracer {

class Metal : public ReflectionMaterial {
public:
    explicit Metal(const Color &albedo);
};

}
