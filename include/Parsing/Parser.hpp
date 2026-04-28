/*
** EPITECH PROJECT, 2026
** G-OOP-400-PAR-4-1-raytracer-22
** File description:
** Parser
*/

#pragma once
#include <iostream>
#include <libconfig.h++>
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

typedef struct Parsing {
    Camera_t c;
    // std::vector<Spheres_t> s;
    // std::vector<Planes_t> p;
} Parsing_t;

class Parser {
    public:
        Parser(std::string filepath) : filepath(filepath) {};
        Parser() = default;
        ~Parser() = default;

        int ReadConfigFile();
        
        // THIS GETTER IS FOR CAMERA
        Camera_t GetCamera();

        // THIS GETTER IS FOR PRIMITIVE
        
        

    private:
        libconfig::Config cfg;
        std::string filepath;
};
