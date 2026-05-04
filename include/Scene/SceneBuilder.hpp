/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** SceneBuilder
*/

#pragma once

#include "scene/Scene.hpp"
#include "scene/SceneData.hpp"

namespace RayTracer {

class SceneBuilder {
public:
    Scene build(const SceneData &data);

private:
    void addSpheres(Scene &scene, const std::vector<SphereData> &spheres);
    void addPlanes(Scene &scene, const std::vector<PlaneData> &planes);
    void addLights(Scene &scene, const LightData &lights);
};

}
