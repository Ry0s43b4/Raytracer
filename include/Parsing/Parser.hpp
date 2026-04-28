/*
** EPITECH PROJECT, 2026
** G-OOP-400-PAR-4-1-raytracer-22
** File description:
** Parser
*/

#pragma once
#include <iostream>
#include <libconfig.h++>

class Parser {
    public:
        Parser(std::string filepath) : filepath(filepath) {};
        Parser() = default;
        ~Parser() = default;

        int ReadConfigFile();
        
        // THIS GETTER IS FOR CAMERA
        int GetCameraResolutionWidth();
        int GetCameraResolutionHeight();
        
        int GetCameraPositionX();
        int GetCameraPositionY();
        int GetCameraPositionZ();

        int GetCameraRotationX();
        int GetCameraRotationY();
        int GetCameraRotationZ();

        double GetCameraFov();

        

    private:
        libconfig::Config cfg;
        std::string filepath;
};
