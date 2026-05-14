/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** SceneParser
*/

#pragma once

#include <libconfig.h++>
#include <string>

#include "Scene/SceneData.hpp"

namespace RayTracer {

class SceneParser {
public:
    explicit SceneParser(const std::string &filepath);

    SceneData parse();

private:
    std::string _filepath;
    libconfig::Config _config;

    void readFile();

    CameraData parseCamera() const;
    std::vector<SphereData> parseSpheres() const;
    std::vector<PlaneData> parsePlanes() const;
    std::vector<CylinderData> parseCylinders() const;
    LightData parseLights() const;

    std::vector<PointLightData> parsePointLights() const;
    std::vector<DirectionalLightData> parseDirectionalLights() const;

    ColorData parseColor(const libconfig::Setting &setting) const;
    TransformData parseTransformIfAny(const libconfig::Setting &setting) const;
};

}
