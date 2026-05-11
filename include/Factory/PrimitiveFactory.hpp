/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** PrimitiveFactory
*/

#pragma once

#include <memory>
#include <string>

#include "Primitives/IPrimitive.hpp"
#include "Primitives/Sphere.hpp"
#include "Primitives/Plane.hpp"
#include "Math/Vector3D.hpp"
#include "Core/Color.hpp"

namespace RayTracer {

class PrimitiveFactory {
public:
    PrimitiveFactory() = default;
    ~PrimitiveFactory() = default;

    std::unique_ptr<IPrimitive> Create(
        const std::string &type,
        const Math::Vector3D &vectorParam,
        double scalarParam,
        const Color &color
    );
};

}
