/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** SceneBuilder
*/

#pragma once

#include "Scene/Scene.hpp"
#include "Scene/SceneData.hpp"
#include "Scene/Camera.hpp"

namespace RayTracer {

class SceneBuilder {
public:
    Scene build(const SceneData &data);

private:
    Camera buildCamera(const CameraData &data);
    void addSpheres(Scene &scene, const std::vector<SphereData> &spheres);
    void addPlanes(Scene &scene, const std::vector<PlaneData> &planes);
    void addCylinders(Scene &scene, const std::vector<CylinderData> &cylinders);
    void addCones(Scene &scene, const std::vector<ConeData> &cones);
    void addLights(Scene &scene, const LightData &lights);
};

}
