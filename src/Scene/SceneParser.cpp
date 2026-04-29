/*
** EPITECH PROJECT, 2026
** G-OOP-400-PAR-4-1-raytracer-22
** File description:
** SceneParser
*/

#include "../../include/Scene/SceneParser.hpp"

int SceneParser::ReadConfigFile()
{
    try {
        cfg.readFile(filepath.c_str());
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

Camera_t SceneParser::GetCamera()
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

std::vector<Sphere_t> SceneParser::GetSphere()
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

std::vector<Plane_t> SceneParser::GetPlane()
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

std::vector<PointLight_t> SceneParser::GetPointLight()
{
    std::vector<PointLight_t> pointlight;
    const libconfig::Setting &pointlights = cfg.lookup("lights.point");

    for (int i = 0; i < pointlights.getLength(); i++) {
        PointLight_t point;
        const libconfig::Setting &p = pointlights[i];
        point.x = p.lookup("x");
        point.y = p.lookup("y");
        point.z = p.lookup("z");
        pointlight.push_back(point);
    }
    return pointlight;
}

std::vector<DirectionalLight_t> SceneParser::GetDirectionalLight()
{
    std::vector<DirectionalLight_t> vd;
    return vd;
}

Light_t SceneParser::GetLight()
{
    Light_t light;
    const libconfig::Setting &lights = cfg.lookup("lights");

    light.ambient = lights.lookup("ambient");
    light.diffuse = lights.lookup("diffuse");
    light.points = GetPointLight();
    light.directionals = GetDirectionalLight();// FONCTION A VOIR CAR PAS IMPLEMENTER DANS LE FICHIER DE CONFIG
    return light;
}
