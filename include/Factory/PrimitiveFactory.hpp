/*
** EPITECH PROJECT, 2026
** G-OOP-400-PAR-4-1-raytracer-22
** File description:
** PrimitiveFactory
*/

#pragma once
#include <memory>
#include "../Math/Vector3D.hpp"
#include "../Math/Point3D.hpp"
#include "../Primitive/IPrimitive.hpp"
#include "../Primitive/Sphere.hpp"
#include "../Primitive/Plane.hpp"

class PrimitiveFactory {
    public:

        PrimitiveFactory() = default;
        ~PrimitiveFactory() = default;

        std::unique_ptr<IPrimitive> Create(std::string type /* et ajouter les info des parametre utiliser*/);
};
