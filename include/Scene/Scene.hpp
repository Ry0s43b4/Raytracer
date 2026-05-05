/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Scene
*/

#pragma once

#include <memory>
#include <vector>

#include "Primitives/IPrimitive.hpp"
#include "Lights/ILight.hpp"
#include "Scene/Camera.hpp"

namespace RayTracer {

class Scene {
public:
    Scene();

    void addPrimitive(std::unique_ptr<IPrimitive> primitive);
    void addLight(std::unique_ptr<ILight> light);
    void setCamera(const Camera &camera);

    const std::vector<std::unique_ptr<IPrimitive>> &primitives() const;
    const std::vector<std::unique_ptr<ILight>> &lights() const;
    const Camera &camera() const;

private:
    std::vector<std::unique_ptr<IPrimitive>> _primitives;
    std::vector<std::unique_ptr<ILight>> _lights;
    Camera _camera;
};

}
