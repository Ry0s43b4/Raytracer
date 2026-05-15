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

struct TransformData {
    bool enabled = false;
    double tx = 0.0;
    double ty = 0.0;
    double tz = 0.0;
    double rx = 0.0;
    double ry = 0.0;
    double rz = 0.0;
};

struct SphereData {
    double x;
    double y;
    double z;
    double radius;
    ColorData color;
    TransformData transform;
    /// Empty string = flat color. Otherwise: "reflection", "refraction", "transparency".
    std::string materialType;
    double materialIor = 1.5;
    /// For transparency material: 0 = opaque, 1 = fully see-through.
    double materialTransmission = 0.65;
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
    TransformData transform;
};

struct ConeData {
    double x;
    double y;
    double z;
    std::string axis;
    double radius;
    double minimum;
    double maximum;
    ColorData color;
};

struct EllipsoidData {
    double x;
    double y;
    double z;
    std::string axis;
    double radius;
    double distance;
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
    std::vector<CylinderData> cylinders;
    std::vector<ConeData> cones;
    std::vector<EllipsoidData> ellipsoids;
    LightData lights;
};

}
