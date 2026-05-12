/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** SceneData
*/

#pragma once

#include <string>
#include <vector>

namespace RayTracer {

struct CameraData {
    int width;
    int height;
    double px;
    double py;
    double pz;
    double rx;
    double ry;
    double rz;
    double fov;
};

struct ColorData {
    int r;
    int g;
    int b;
};

struct SphereData {
    double x;
    double y;
    double z;
    double radius;
    ColorData color;
};

struct PlaneData {
    std::string axis;
    double position;
    ColorData color;
};

struct CylinderData {
    double x;
    double y;
    double z;
    std::string axis;
    double radius;
    ColorData color;
};

struct DirectionalLightData {
    double x;
    double y;
    double z;
};

struct PointLightData {
    double x;
    double y;
    double z;
};

struct LightData {
    double ambient;
    double diffuse;
    std::vector<PointLightData> points;
    std::vector<DirectionalLightData> directionals;
};

struct SceneData {
    CameraData camera;
    std::vector<SphereData> spheres;
    std::vector<PlaneData> planes;
    LightData lights;
};

}
