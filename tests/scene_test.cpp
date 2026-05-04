#include <criterion/criterion.h>
#include <memory>

#include "Lights/ILight.hpp"
#include "Primitives/IPrimitive.hpp"
#include "Scene/Scene.hpp"

namespace {

class FakePrimitive : public IPrimitive {
};

class FakeLight : public ILight {
};

}

Test(Scene, starts_empty)
{
    RayTracer::Scene scene;

    cr_assert_eq(scene.primitives().size(), 0);
    cr_assert_eq(scene.lights().size(), 0);
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
