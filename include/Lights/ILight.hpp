/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** ILight
*/

#pragma once

#include <memory>
#include <vector>

#include "Math/Vector3D.hpp"
#include "Core/Color.hpp"
#include "Core/Intersection.hpp"
#include "Math/Ray.hpp"

namespace RayTracer {

class IPrimitive;

class ILight {
public:
    virtual ~ILight() = default;

    virtual Color computeLight(
        const Intersection &intersection,
        const Math::Vector3D &viewDir,
        const Ray &eyeRay,
        const std::vector<std::unique_ptr<IPrimitive>> &primitives
    ) const = 0;
};

}
