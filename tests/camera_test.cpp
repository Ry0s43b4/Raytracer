#include <criterion/criterion.h>

#include "Scene/Camera.hpp"

Test(Camera, generates_forward_ray_without_rotation)
{
    RayTracer::Camera camera(
        800,
        600,
        Math::Vector3D(0.0, 0.0, 0.0),
        Math::Vector3D(0.0, 0.0, 0.0),
        60.0
    );

    RayTracer::Ray ray = camera.generateRay(400, 300);

    cr_assert_float_eq(ray.origin().x, 0.0, 1e-6);
    cr_assert_float_eq(ray.origin().y, 0.0, 1e-6);
    cr_assert_float_eq(ray.origin().z, 0.0, 1e-6);
    cr_assert(ray.direction().z > 0.99);
}

Test(Camera, applies_rotation_to_generated_ray)
{
    RayTracer::Camera camera(
        800,
        600,
        Math::Vector3D(0.0, 0.0, 0.0),
        Math::Vector3D(0.0, 45.0, 0.0),
        60.0
    );

    RayTracer::Ray ray = camera.generateRay(400, 300);

    cr_assert(ray.direction().x > 0.6);
    cr_assert(ray.direction().z > 0.6);
}
