/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Scene
*/

#include "Scene/Scene.hpp"

namespace RayTracer {

void Scene::addPrimitive(std::unique_ptr<IPrimitive> primitive)
{
    _primitives.push_back(std::move(primitive));
}

void Scene::addLight(std::unique_ptr<ILight> light)
{
    _lights.push_back(std::move(light));
}

const std::vector<std::unique_ptr<IPrimitive>> &Scene::primitives() const
{
    return _primitives;
}

const std::vector<std::unique_ptr<ILight>> &Scene::lights() const
{
    return _lights;
}

}
