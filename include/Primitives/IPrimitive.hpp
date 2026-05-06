/*
** EPITECH PROJECT, 2026
** G-OOP-400-PAR-4-1-raytracer-22
** File description:
** IPrimitive
*/

#pragma once
#include "Core/Intersection.hpp"
#include "Math/Ray.hpp"
#include "Core/Color.hpp"

class IPrimitive {
    public:
        virtual ~IPrimitive() = default;
        virtual RayTracer::Intersection intersect(RayTracer::Ray r) = 0;
};
