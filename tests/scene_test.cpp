#include <criterion/criterion.h>
#include <memory>

#include "Lights/ILight.hpp"
#include "Math/Vector3D.hpp"
#include "Primitives/IPrimitive.hpp"
#include "Scene/Camera.hpp"
#include "Scene/Scene.hpp"

namespace {

class FakePrimitive : public RayTracer::IPrimitive {
public:
    RayTracer::Intersection intersect(const RayTracer::Ray &) const override
    {
        return RayTracer::Intersection();
    }
};

class FakeLight : public RayTracer::ILight {
public:
    RayTracer::Color computeLight(
        const RayTracer::Intersection &,
        const Math::Vector3D &
    ) const override
    {
        return RayTracer::Color(0, 0, 0);
    }
};

}

Test(Scene, starts_empty)
{
    RayTracer::Scene scene;

    cr_assert_eq(scene.primitives().size(), 0);
    cr_assert_eq(scene.lights().size(), 0);
    cr_assert_eq(scene.camera().width(), 1);
    cr_assert_eq(scene.camera().height(), 1);
}

Test(Scene, stores_added_primitive)
{
    RayTracer::Scene scene;

    scene.addPrimitive(std::make_unique<FakePrimitive>());

    cr_assert_eq(scene.primitives().size(), 1);
    cr_assert_not_null(dynamic_cast<FakePrimitive *>(scene.primitives()[0].get()));
}

Test(Scene, stores_added_light)
{
    RayTracer::Scene scene;

    scene.addLight(std::make_unique<FakeLight>());

    cr_assert_eq(scene.lights().size(), 1);
    cr_assert_not_null(dynamic_cast<FakeLight *>(scene.lights()[0].get()));
}

Test(Scene, preserves_insertion_order)
{
    RayTracer::Scene scene;

    scene.addPrimitive(std::make_unique<FakePrimitive>());
    scene.addPrimitive(std::make_unique<FakePrimitive>());
    scene.addLight(std::make_unique<FakeLight>());
    scene.addLight(std::make_unique<FakeLight>());

    cr_assert_eq(scene.primitives().size(), 2);
    cr_assert_eq(scene.lights().size(), 2);
    cr_assert_not_null(dynamic_cast<FakePrimitive *>(scene.primitives()[0].get()));
    cr_assert_not_null(dynamic_cast<FakePrimitive *>(scene.primitives()[1].get()));
    cr_assert_not_null(dynamic_cast<FakeLight *>(scene.lights()[0].get()));
    cr_assert_not_null(dynamic_cast<FakeLight *>(scene.lights()[1].get()));
}

Test(Scene, stores_assigned_camera)
{
    RayTracer::Scene scene;
    RayTracer::Camera camera(
        1920,
        1080,
        Math::Vector3D(1.0, 2.0, 3.0),
        Math::Vector3D(10.0, 20.0, 30.0),
        72.0
    );

    scene.setCamera(camera);

    cr_assert_eq(scene.camera().width(), 1920);
    cr_assert_eq(scene.camera().height(), 1080);
    cr_assert_float_eq(scene.camera().position().x, 1.0, 1e-6);
    cr_assert_float_eq(scene.camera().rotation().y, 20.0, 1e-6);
    cr_assert_float_eq(scene.camera().fov(), 72.0, 1e-6);
}
