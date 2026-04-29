/*
** EPITECH PROJECT, 2026
** G-OOP-400-PAR-4-1-raytracer-22
** File description:
** SceneParser
*/

#pragma once
#include <iostream>
#include <libconfig.h++>
#include <string>
#include <vector>

typedef struct Camera {
    int width;
    int height;
    int px;
    int py;
    int pz;
    int rx;
    int ry;
    int rz;
    double fov;
} Camera_t;

typedef struct Sphere
{
    int x;
    int y;
    int z;
    int r;
    int cr;
    int cg;
    int cb;
} Sphere_t;

typedef struct Plane
{
    std::string axis;
    int position;
    int cr;
    int cg;
    int cb;
} Plane_t;

typedef struct PointLight {
    int x;
    int y;
    int z;
} PointLight_t;

typedef struct DirectionalLight {
    int x;
    int y;
    int z;
} DirectionalLight_t;

typedef struct Light {
    double ambient;
    double diffuse;
    std::vector<PointLight_t> points;
    std::vector<DirectionalLight_t> directionals;
} Light_t;

typedef struct Parsing {
    Camera_t c;
    std::vector<Sphere_t> s;
    std::vector<Plane_t> p;
} Parsing_t;

class SceneParser {
    public:
        SceneParser(std::string filepath) : filepath(filepath) {};
        SceneParser() = default;
        ~SceneParser() = default;

        int ReadConfigFile();
        
        // THIS GETTER IS FOR CAMERA
        Camera_t GetCamera();

        // THIS GETTER IS FOR SPHERES
        std::vector<Sphere_t> GetSphere();

        // THIS GETTER IS FOR PLANES
        std::vector<Plane_t> GetPlane();

        // THIS GETTER IS FOR LIGHTS
        Light_t GetLight();
        std::vector<PointLight_t> GetPointLight();
        std::vector<DirectionalLight_t> GetDirectionalLight(); // FONCTION A VOIR CAR PAS IMPLEMENTER DANS LE FICHIER DE CONFIG
    private:
        libconfig::Config cfg;
        std::string filepath;
};
