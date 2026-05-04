/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Scene
*/

#pragma once

#include <memory>
#include <vector>

#include "primitives/IPrimitive.hpp"
#include "lights/ILight.hpp"

namespace RayTracer {

class Scene {
public:
    void addPrimitive(std::unique_ptr<IPrimitive> primitive);
    void addLight(std::unique_ptr<ILight> light);

    const std::vector<std::unique_ptr<IPrimitive>> &primitives() const;
    const std::vector<std::unique_ptr<ILight>> &lights() const;

private:
    std::vector<std::unique_ptr<IPrimitive>> _primitives;
    std::vector<std::unique_ptr<ILight>> _lights;
};

}
