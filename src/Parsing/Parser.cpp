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

std::vector<Sphere_t> Parser::GetSphere()
{
    std::vector<Sphere_t> vs;
    const libconfig::Setting &spheres = cfg.lookup("primitives.spheres");

    for (int i = 0; i < spheres.getLength(); i++) {
        const libconfig::Setting &s = spheres[i];
        Sphere_t sphere;
        sphere.x = s.lookup("x");
        sphere.y = s.lookup("y");
        sphere.z = s.lookup("z");
        sphere.r = s.lookup("r");
        const libconfig::Setting &color = s.lookup("color");
        sphere.cr = color.lookup("r");
        sphere.cg = color.lookup("g");
        sphere.cb = color.lookup("b");
        vs.push_back(sphere);
    }
    return vs;
}

std::vector<Plane_t> Parser::GetPlane()
{
    std::vector<Plane_t> vp;
    const libconfig::Setting &planes = cfg.lookup("primitives.planes");

    for (int i = 0; i < planes.getLength(); i++) {
        const libconfig::Setting &p = planes[i];
        Plane_t plane;
        plane.axis = p.lookup("axis").c_str();
        plane.position = p.lookup("position");
        const libconfig::Setting &color = p.lookup("color");
        plane.cr = color.lookup("r");
        plane.cg = color.lookup("g");
        plane.cb = color.lookup("b");
        vp.push_back(plane);
    }
    return vp;
}
