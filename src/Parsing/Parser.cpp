/*
** EPITECH PROJECT, 2026
** G-OOP-400-PAR-4-1-raytracer-22
** File description:
** Parser
*/

#include "../../include/Parsing/Parser.hpp"

int Parser::ReadConfigFile()
{
    try {
        cfg.readFile(filepath);
    } catch(const libconfig::FileIOException &fioex) {
        std::cerr << "I/O error while reading file." << std::endl;
        return 84;
    } catch(const libconfig::ParseException &pex) {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                << " - " << pex.getError() << std::endl;
        return 84;
    }
    return 0;
}

int Parser::GetCameraResolutionWidth()
{
    return cfg.lookup("camera.resolution.width");
}

int Parser::GetCameraResolutionHeight()
{
    return cfg.lookup("camera.resolution.height");
}

int Parser::GetCameraPositionX()
{
    return cfg.lookup("camera.position.x");
}
int Parser::GetCameraPositionY()
{
    return cfg.lookup("camera.position.y");
}

int Parser::GetCameraPositionZ()
{
    return cfg.lookup("camera.position.z");
}

int Parser::GetCameraRotationX()
{
    return cfg.lookup("camera.rotation.x");
}

int Parser::GetCameraRotationY()
{
    return cfg.lookup("camera.rotation.y");
}

int Parser::GetCameraRotationZ()
{
    return cfg.lookup("camera.rotation.z");
}

double Parser::GetCameraFov()
{
    return cfg.lookup("camera.fieldOfView");
}
