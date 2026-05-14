/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** SceneParser
*/

#include "Scene/SceneParser.hpp"
#include "Core/RaytracerError.hpp"

namespace RayTracer {

SceneParser::SceneParser(const std::string &filepath)
    : _filepath(filepath)
{
}

SceneData SceneParser::parse()
{
    readFile();

    SceneData data;

    data.camera = parseCamera();
    data.spheres = parseSpheres();
    data.planes = parsePlanes();
    data.lights = parseLights();
    data.cylinders = parseCylinders();
    data.cones = parseCones();

    return data;
}

void SceneParser::readFile()
{
    try {
        _config.readFile(_filepath.c_str());
    } catch (const libconfig::FileIOException &) {
        throw RaytracerError("I/O error while reading scene file: " + _filepath);
    } catch (const libconfig::ParseException &e) {
        throw RaytracerError(
            "Parse error in " + std::string(e.getFile()) +
            ":" + std::to_string(e.getLine()) +
            " - " + e.getError()
        );
    }
}

CameraData SceneParser::parseCamera() const
{
    CameraData camera;

    try {
        camera.width = _config.lookup("camera.resolution.width");
        camera.height = _config.lookup("camera.resolution.height");

        camera.px = _config.lookup("camera.position.x");
        camera.py = _config.lookup("camera.position.y");
        camera.pz = _config.lookup("camera.position.z");

        camera.rx = _config.lookup("camera.rotation.x");
        camera.ry = _config.lookup("camera.rotation.y");
        camera.rz = _config.lookup("camera.rotation.z");

        camera.fov = _config.lookup("camera.fieldOfView");
    } catch (const libconfig::SettingException &e) {
        throw RaytracerError("Invalid or missing camera setting: " + std::string(e.getPath()));
    }

    return camera;
}

std::vector<SphereData> SceneParser::parseSpheres() const
{
    std::vector<SphereData> spheres;

    if (!_config.exists("primitives.spheres"))
        return spheres;

    const libconfig::Setting &settings = _config.lookup("primitives.spheres");

    for (int i = 0; i < settings.getLength(); ++i) {
        const libconfig::Setting &s = settings[i];

        SphereData sphere;
        sphere.x = s.lookup("x");
        sphere.y = s.lookup("y");
        sphere.z = s.lookup("z");
        sphere.radius = s.lookup("r");
        sphere.color = parseColor(s.lookup("color"));

        spheres.push_back(sphere);
    }

    return spheres;
}

std::vector<PlaneData> SceneParser::parsePlanes() const
{
    std::vector<PlaneData> planes;

    if (!_config.exists("primitives.planes"))
        return planes;

    const libconfig::Setting &settings = _config.lookup("primitives.planes");

    for (int i = 0; i < settings.getLength(); ++i) {
        const libconfig::Setting &p = settings[i];

        PlaneData plane;
        plane.axis = static_cast<const char *>(p.lookup("axis"));
        plane.position = p.lookup("position");
        plane.color = parseColor(p.lookup("color"));

        planes.push_back(plane);
    }

    return planes;
}

std::vector<CylinderData> SceneParser::parseCylinders() const
{
    std::vector<CylinderData> cylinders;

    if (!_config.exists("primitives.cylinders"))
        return cylinders;

    const libconfig::Setting &settings = _config.lookup("primitives.cylinders");

    for (int i = 0; i < settings.getLength(); ++i) {
        const libconfig::Setting &c = settings[i];

        CylinderData cylinder;
        cylinder.x = c.lookup("x");
        cylinder.y = c.lookup("y");
        cylinder.z = c.lookup("z");
        cylinder.axis = static_cast<const char *>(c.lookup("axis"));
        cylinder.radius = c.lookup("r");
        cylinder.color = parseColor(c.lookup("color"));

        cylinders.push_back(cylinder);
    }

    return cylinders;
}

std::vector<ConeData> SceneParser::parseCones() const
{
    std::vector<ConeData> cones;

    if (!_config.exists("primitives.cones"))
        return cones;

    const libconfig::Setting &settings = _config.lookup("primitives.cones");

    for (int i = 0; i < settings.getLength(); ++i) {
        const libconfig::Setting &c = settings[i];

        ConeData cone;
        cone.x = c.lookup("x");
        cone.y = c.lookup("y");
        cone.z = c.lookup("z");
        cone.axis = static_cast<const char *>(c.lookup("axis"));
        cone.radius = c.lookup("r");
        cone.maximum = c.lookup("max");
        cone.minimum = c.lookup("min");
        cone.color = parseColor(c.lookup("color"));

        cones.push_back(cone);
    }

    return cones;
}

LightData SceneParser::parseLights() const
{
    LightData lights;

    try {
        lights.ambient = _config.lookup("lights.ambient");
        lights.diffuse = _config.lookup("lights.diffuse");
        lights.points = parsePointLights();
        lights.directionals = parseDirectionalLights();
    } catch (const libconfig::SettingException &e) {
        throw RaytracerError("Invalid or missing light setting: " + std::string(e.getPath()));
    }

    return lights;
}

std::vector<PointLightData> SceneParser::parsePointLights() const
{
    std::vector<PointLightData> lights;

    if (!_config.exists("lights.point"))
        return lights;

    const libconfig::Setting &settings = _config.lookup("lights.point");

    for (int i = 0; i < settings.getLength(); ++i) {
        const libconfig::Setting &p = settings[i];

        PointLightData light;
        light.x = p.lookup("x");
        light.y = p.lookup("y");
        light.z = p.lookup("z");

        lights.push_back(light);
    }

    return lights;
}

std::vector<DirectionalLightData> SceneParser::parseDirectionalLights() const
{
    std::vector<DirectionalLightData> lights;

    if (!_config.exists("lights.directional"))
        return lights;

    const libconfig::Setting &settings = _config.lookup("lights.directional");

    for (int i = 0; i < settings.getLength(); ++i) {
        const libconfig::Setting &d = settings[i];

        DirectionalLightData light;
        light.x = d.lookup("x");
        light.y = d.lookup("y");
        light.z = d.lookup("z");

        lights.push_back(light);
    }

    return lights;
}

ColorData SceneParser::parseColor(const libconfig::Setting &setting) const
{
    ColorData color;

    color.r = setting.lookup("r");
    color.g = setting.lookup("g");
    color.b = setting.lookup("b");

    return color;
}

}
