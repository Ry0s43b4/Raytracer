/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** PhongMaterial
*/

#pragma once

#include "Materials/IMaterial.hpp"

namespace RayTracer {

class PhongMaterial : public IMaterial {
public:
    PhongMaterial(double shininess, double specularStrength);

    Color shade(
        const Ray &r_in,
        const Math::Vector3D &point,
        const Math::Vector3D &normal,
        bool frontFace,
        const Color &directLighting,
        const std::function<Color(const Ray &)> &traceRay
    ) const override;

    bool   needsSpecular()     const override { return true; }
    double shininess()         const override { return _shininess; }
    double specularStrength()  const override { return _specularStrength; }

private:
    double _shininess;
    double _specularStrength;
};

}
