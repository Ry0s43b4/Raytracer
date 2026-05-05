/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Renderer
*/

#pragma once

#include "Scene/Scene.hpp"
#include "Core/Image.hpp"
#include "Math/Ray.hpp"

namespace RayTracer {

class Renderer {
public:
    Image render(const Scene &scene) const;

private:
    Intersection castRay(const RayTracer::Ray &ray, const Scene &scene) const;

    Color computeColor(
        const Intersection &intersection,
        const RayTracer::Ray &ray,
        const Scene &scene
    ) const;
};

}
