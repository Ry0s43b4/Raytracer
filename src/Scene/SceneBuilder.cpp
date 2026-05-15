/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** SceneBuilder
*/

#include <memory>
#include <string>

#include "Scene/SceneBuilder.hpp"
#include "Scene/Camera.hpp"
#include "Primitives/Sphere.hpp"
#include "Primitives/Plane.hpp"
#include "Primitives/Cylinder.hpp"
#include "Primitives/Cone.hpp"
#include "Primitives/Ellipsoid.hpp"
#include "Primitives/TransformedPrimitive.hpp"
#include "Transformation/TransformationComposer.hpp"
#include "Lights/AmbientLight.hpp"
#include "Lights/DirectionalLight.hpp"
#include "Lights/PointLight.hpp"
#include "Math/Vector3D.hpp"
#include "Core/Color.hpp"
#include "Core/RaytracerError.hpp"
#include "Materials/IMaterial.hpp"
#include "Materials/PhongMaterial.hpp"
#include "Materials/ReflectionMaterial.hpp"
#include "Materials/RefractionMaterial.hpp"
#include "Materials/TransparencyMaterial.hpp"

namespace RayTracer {

namespace {

std::shared_ptr<IMaterial> makeSphereMaterial(const SphereData &s)
{
    Color surface(s.color.r, s.color.g, s.color.b);

    if (s.materialType.empty())
        return nullptr;

    if (s.materialType == "phong")
        return std::make_shared<PhongMaterial>(s.materialShininess, s.materialSpecularStrength);

    if (s.materialType == "reflection")
        return std::make_shared<ReflectionMaterial>(surface);

    if (s.materialType == "refraction")
        return std::make_shared<RefractionMaterial>(surface, s.materialIor);

    if (s.materialType == "transparency")
        return std::make_shared<TransparencyMaterial>(s.materialTransmission);

    throw RaytracerError("Unknown sphere material type: " + s.materialType);
}

}

Scene SceneBuilder::build(const SceneData &data)
{
    Scene scene;

    scene.setCamera(buildCamera(data.camera));
    addSpheres(scene, data.spheres);
    addPlanes(scene, data.planes);
    addLights(scene, data.lights);
    addCylinders(scene, data.cylinders);
    addCones(scene, data.cones);
    addEllipsoids(scene, data.ellipsoids);
    return scene;
}

Camera SceneBuilder::buildCamera(const CameraData &data)
{
    return Camera(
        data.width,
        data.height,
        Math::Vector3D(data.px, data.py, data.pz),
        Math::Vector3D(data.rx, data.ry, data.rz),
        data.fov
    );
}

void SceneBuilder::addSpheres(Scene &scene, const std::vector<SphereData> &spheres)
{
    for (const auto &s : spheres) {
        Color color(s.color.r, s.color.g, s.color.b);
        auto material = makeSphereMaterial(s);

        if (s.transform.enabled) {
            const Math::Vector3D translation(
                s.x + s.transform.tx,
                s.y + s.transform.ty,
                s.z + s.transform.tz
            );
            const Math::Vector3D euler(s.transform.rx, s.transform.ry, s.transform.rz);
            const TransformationComposer pose(translation, euler);

            scene.addPrimitive(std::make_unique<TransformedPrimitive>(
                std::make_unique<Sphere>(
                    Math::Vector3D(0.0, 0.0, 0.0),
                    s.radius,
                    color,
                    material
                ),
                pose
            ));
        } else {
            scene.addPrimitive(std::make_unique<Sphere>(
                Math::Vector3D(s.x, s.y, s.z),
                s.radius,
                color,
                material
            ));
        }
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

void SceneBuilder::addCylinders(Scene &scene, const std::vector<CylinderData> &cylinders)
{
    for (const auto &p : cylinders) {
        Color color(p.color.r, p.color.g, p.color.b);

        if (p.transform.enabled) {
            const Math::Vector3D translation(
                p.x + p.transform.tx,
                p.y + p.transform.ty,
                p.z + p.transform.tz
            );
            const Math::Vector3D euler(p.transform.rx, p.transform.ry, p.transform.rz);
            const TransformationComposer pose(translation, euler);

            scene.addPrimitive(std::make_unique<TransformedPrimitive>(
                std::make_unique<Cylinder>(
                    Math::Vector3D(0.0, 0.0, 0.0),
                    Math::Vector3D(0.0, 0.0, 1.0),
                    p.radius,
                    color,
                    nullptr
                ),
                pose
            ));
        } else {
            Math::Vector3D normal;

            if (p.axis == "X")
                normal = Math::Vector3D(1, 0, 0);
            else if (p.axis == "Y")
                normal = Math::Vector3D(0, 1, 0);
            else
                normal = Math::Vector3D(0, 0, 1);

            scene.addPrimitive(std::make_unique<Cylinder>(
                Math::Vector3D(p.x, p.y, p.z),
                normal,
                p.radius,
                color,
                nullptr
            ));
        }
    }
}

void SceneBuilder::addCones(Scene &scene, const std::vector<ConeData> &cones)
{
    for (const auto &p : cones) {
        Math::Vector3D normal;

        if (p.axis == "X")
            normal = Math::Vector3D(1, 0, 0);
        else if (p.axis == "Y")
            normal = Math::Vector3D(0, 1, 0);
        else
            normal = Math::Vector3D(0, 0, 1);

        scene.addPrimitive(std::make_unique<Cone>(
            Math::Vector3D(p.x, p.y, p.z),
            normal,
            p.radius,
            p.maximum,
            p.minimum,
            Color(p.color.r, p.color.g, p.color.b)
        ));
    }
}

void SceneBuilder::addEllipsoids(Scene &scene, const std::vector<EllipsoidData> &ellipsoids)
{
    for (const auto &p : ellipsoids) {
        Math::Vector3D normal;

        if (p.axis == "X")
            normal = Math::Vector3D(1, 0, 0);
        else if (p.axis == "Y")
            normal = Math::Vector3D(0, 1, 0);
        else
            normal = Math::Vector3D(0, 0, 1);

        scene.addPrimitive(std::make_unique<Ellipsoid>(
            Math::Vector3D(p.x, p.y, p.z),
            normal,
            p.radius,
            p.distance,
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

    for (const auto &p : lights.points) {
        scene.addLight(std::make_unique<PointLight>(
            Math::Vector3D(p.x, p.y, p.z),
            lights.diffuse
        ));
    }
}

}
