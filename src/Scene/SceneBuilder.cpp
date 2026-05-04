/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** SceneBuilder
*/

#include <memory>

#include "Scene/SceneBuilder.hpp"
#include "Primitives/Sphere.hpp"
#include "Primitives/Plane.hpp"
#include "Lights/AmbientLight.hpp"
#include "Lights/DirectionalLight.hpp"
#include "Math/Vector3D.hpp"
#include "Core/Color.hpp"

namespace RayTracer {

Scene SceneBuilder::build(const SceneData &data)
{
    Scene scene;

    addSpheres(scene, data.spheres);
    addPlanes(scene, data.planes);
    addLights(scene, data.lights);

    return scene;
}

void SceneBuilder::addSpheres(Scene &scene, const std::vector<SphereData> &spheres)
{
    for (const auto &s : spheres) {
        scene.addPrimitive(std::make_unique<Sphere>(
            Math::Vector3D(s.x, s.y, s.z),
            s.radius,
            Color(s.color.r, s.color.g, s.color.b)
        ));
    }
}

void SceneBuilder::addPlanes(Scene &scene, const std::vector<PlaneData> &planes)
{
    for (const auto &p : planes) {
        Math::Vector3D normal;

        if (p.axis == "X")
            normal = Math::Vector3D(1, 0, 0);
        else if (p.axis == "Y")
            normal = Math::Vector3D(0, 1, 0);
        else
            normal = Math::Vector3D(0, 0, 1);

        scene.addPrimitive(std::make_unique<Plane>(
            normal,
            p.position,
            Color(p.color.r, p.color.g, p.color.b)
        ));
    }
}

void SceneBuilder::addLights(Scene &scene, const LightData &lights)
{
    scene.addLight(std::make_unique<AmbientLight>(lights.ambient));

    for (const auto &d : lights.directionals) {
        scene.addLight(std::make_unique<DirectionalLight>(
            Math::Vector3D(d.x, d.y, d.z),
            lights.diffuse
        ));
    }
}

}
