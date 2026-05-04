#include <criterion/criterion.h>
#include <cstring>
#include <string>

#include "Core/RaytracerError.hpp"
#include "Scene/SceneParser.hpp"

namespace {

std::string scenePath(const std::string &filename)
{
    std::string currentFile = __FILE__;
    std::size_t lastSlash = currentFile.find_last_of("/\\");
    std::string baseDir = lastSlash == std::string::npos
        ? "."
        : currentFile.substr(0, lastSlash);

    return baseDir + "/scenes/" + filename;
}

}

Test(SceneParser, parses_complete_scene_file)
{
    RayTracer::SceneParser parser(scenePath("valid_scene.cfg"));

    RayTracer::SceneData data = parser.parse();

    cr_assert_eq(data.camera.width, 1280);
    cr_assert_eq(data.camera.height, 720);
    cr_assert_float_eq(data.camera.px, 0.0, 1e-6);
    cr_assert_float_eq(data.camera.py, -100.0, 1e-6);
    cr_assert_float_eq(data.camera.pz, 20.0, 1e-6);
    cr_assert_float_eq(data.camera.fov, 72.0, 1e-6);

    cr_assert_eq(data.spheres.size(), 2);
    cr_assert_float_eq(data.spheres[0].x, 60.0, 1e-6);
    cr_assert_float_eq(data.spheres[0].radius, 25.0, 1e-6);
    cr_assert_eq(data.spheres[0].color.r, 255);
    cr_assert_eq(data.spheres[1].color.g, 255);

    cr_assert_eq(data.planes.size(), 1);
    cr_assert_str_eq(data.planes[0].axis.c_str(), "Z");
    cr_assert_float_eq(data.planes[0].position, -20.0, 1e-6);
    cr_assert_eq(data.planes[0].color.b, 255);

    cr_assert_float_eq(data.lights.ambient, 0.4, 1e-6);
    cr_assert_float_eq(data.lights.diffuse, 0.6, 1e-6);
    cr_assert_eq(data.lights.points.size(), 1);
    cr_assert_float_eq(data.lights.points[0].x, 400.0, 1e-6);
    cr_assert_eq(data.lights.directionals.size(), 1);
    cr_assert_float_eq(data.lights.directionals[0].z, -1.0, 1e-6);
}

Test(SceneParser, accepts_scene_without_optional_primitive_and_light_lists)
{
    RayTracer::SceneParser parser(scenePath("minimal_scene.cfg"));

    RayTracer::SceneData data = parser.parse();

    cr_assert_eq(data.spheres.size(), 0);
    cr_assert_eq(data.planes.size(), 0);
    cr_assert_eq(data.lights.points.size(), 0);
    cr_assert_eq(data.lights.directionals.size(), 0);
    cr_assert_float_eq(data.lights.ambient, 0.2, 1e-6);
    cr_assert_float_eq(data.lights.diffuse, 0.8, 1e-6);
}

Test(SceneParser, throws_for_missing_scene_file)
{
    RayTracer::SceneParser parser(scenePath("does_not_exist.cfg"));
    std::string expectedMessage =
        "I/O error while reading scene file: " + scenePath("does_not_exist.cfg");

    try {
        (void)parser.parse();
        cr_assert_fail("Expected parser to throw for a missing file");
    } catch (const RayTracer::RaytracerError &error) {
        cr_assert_str_eq(error.what(), expectedMessage.c_str());
    }
}

Test(SceneParser, throws_for_missing_required_camera_setting)
{
    RayTracer::SceneParser parser(scenePath("missing_camera_field.cfg"));

    try {
        (void)parser.parse();
        cr_assert_fail("Expected parser to throw for a missing camera field");
    } catch (const RayTracer::RaytracerError &error) {
        cr_assert_str_eq(
            error.what(),
            "Invalid or missing camera setting: camera.fieldOfView"
        );
    }
}

Test(SceneParser, throws_for_invalid_scene_syntax)
{
    RayTracer::SceneParser parser(scenePath("invalid_syntax.cfg"));

    try {
        (void)parser.parse();
        cr_assert_fail("Expected parser to throw for invalid syntax");
    } catch (const RayTracer::RaytracerError &error) {
        cr_assert_not_null(std::strstr(error.what(), "Parse error in "));
        cr_assert_not_null(std::strstr(error.what(), "invalid_syntax.cfg"));
    }
}
