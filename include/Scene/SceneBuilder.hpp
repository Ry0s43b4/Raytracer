/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** SceneBuilder
*/

#pragma once

#include "Scene.hpp"
#include "SceneData.hpp"
#include "Camera.hpp"

namespace RayTracer {

class SceneBuilder {
public:
    Scene build(const SceneData &data);

private:
    Camera buildCamera(const CameraData &data);
    void addSpheres(Scene &scene, const std::vector<SphereData> &spheres);
    void addPlanes(Scene &scene, const std::vector<PlaneData> &planes);
    void addLights(Scene &scene, const LightData &lights);
};

}
