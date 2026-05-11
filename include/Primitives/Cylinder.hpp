/*
** EPITECH PROJECT, 2026
** G-OOP-400-PAR-4-1-raytracer-22
** File description:
** Cylinder
*/

#include "Primitives/IPrimitive.hpp"
#include "Math/Vector3D.hpp"
#include "Core/Color.hpp"

namespace RayTracer {

class Cylinder : public IPrimitive {
public:
    Cylinder(
        const Math::Vector3D &center,
        const Math::Vector3D &cylinderAxis,
        double radius,
        double maximum,
        const Color &color
    );

    Intersection intersect(const Ray &ray) const override;

private:
    Math::Vector3D _center;
    Math::Vector3D _cylinderAxis;
    double _radius;
    double _maximum;
    Color _color;
};

}