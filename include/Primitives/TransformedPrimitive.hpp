/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** TransformedPrimitive — Decorator: child in local space + rigid pose in world
*/

#pragma once

#include <memory>

#include "Primitives/IPrimitive.hpp"
#include "Transformation/TransformationComposer.hpp"

namespace RayTracer {

class TransformedPrimitive : public IPrimitive {
public:
    TransformedPrimitive(
        std::unique_ptr<IPrimitive> child,
        const TransformationComposer &pose
    );

    Intersection intersect(const Ray &ray) const override;

private:
    std::unique_ptr<IPrimitive> _child;
    TransformationComposer _pose;
};

}
