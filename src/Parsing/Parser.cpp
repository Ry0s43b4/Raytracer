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

Camera_t Parser::GetCamera()
{
    Camera_t camera;

    camera.width = cfg.lookup("camera.resolution.width");
    camera.height = cfg.lookup("camera.resolution.height");
    camera.px = cfg.lookup("camera.position.x");
    camera.py = cfg.lookup("camera.position.y");
    camera.pz = cfg.lookup("camera.position.z");
    camera.rx = cfg.lookup("camera.rotation.x");
    camera.ry = cfg.lookup("camera.rotation.y");
    camera.rz = cfg.lookup("camera.rotation.z");
    camera.fov = cfg.lookup("camera.fieldOfView");
    return camera;
}
