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
    static constexpr int kMaxTraceDepth = 8;

    Color traceRay(const Ray &ray, const Scene &scene, int depth) const;
    Intersection castRay(const Ray &ray, const Scene &scene, double tMin) const;

    Color computeDirectLighting(
        const Intersection &intersection,
        const Ray &eyeRay,
        const Scene &scene
    ) const;

    Color computeSpecularLighting(
        const Intersection &intersection,
        const Math::Vector3D &viewDir,
        double shininess,
        double specularStrength,
        const Scene &scene
    ) const;
};

}
