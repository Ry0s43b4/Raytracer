/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** ILight
*/

#pragma once

#include "Math/Vector3D.hpp"
#include "Core/Color.hpp"
#include "Core/Intersection.hpp"

namespace RayTracer {

class ILight {
public:
    virtual ~ILight() = default;

    virtual Color computeLight(
        const Intersection &intersection,
        const Math::Vector3D &viewDir
    ) const = 0;
};

}
