/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Scene
*/

#pragma once

#include <memory>
#include <vector>

#include "Scene/Camera.hpp"
#include "Primitives/IPrimitive.hpp"
#include "Lights/ILight.hpp"

namespace RayTracer {

class Scene {
public:
    void setCamera(const Camera &camera);
    void addPrimitive(std::unique_ptr<IPrimitive> primitive);
    void addLight(std::unique_ptr<ILight> light);

    const Camera &camera() const;
    const std::vector<std::unique_ptr<IPrimitive>> &primitives() const;
    const std::vector<std::unique_ptr<ILight>> &lights() const;

private:
    Camera _camera;
    std::vector<std::unique_ptr<IPrimitive>> _primitives;
    std::vector<std::unique_ptr<ILight>> _lights;
};

}
