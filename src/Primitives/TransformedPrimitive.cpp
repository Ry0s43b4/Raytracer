/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** TransformedPrimitive
*/

#include "Primitives/TransformedPrimitive.hpp"

namespace RayTracer {

TransformedPrimitive::TransformedPrimitive(
    std::unique_ptr<IPrimitive> child,
    const TransformationComposer &pose
)
    : _child(std::move(child)),
      _pose(pose)
{
}

Intersection TransformedPrimitive::intersect(const Ray &ray) const
{
    const Ray localRay = _pose.worldToLocalRay(ray);
    Intersection hit = _child->intersect(localRay);

    if (!hit.hasHit())
        return hit;

    const Math::Vector3D worldPoint = _pose.localToWorldPoint(hit.point());
    const Math::Vector3D worldNormal = _pose.localToWorldNormal(hit.normal()).normalized();

    const Math::Vector3D v = worldPoint - ray.origin();
    const double tWorld = v.dot(ray.direction());

    return Intersection(true, tWorld, worldPoint, worldNormal, hit.color());
}

}
