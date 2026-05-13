/*
** EPITECH PROJECT, 2026
** G-OOP-400-PAR-4-1-raytracer-22
** File description:
** Cone
*/

#include "Primitives/IPrimitive.hpp"
#include "Math/Vector3D.hpp"
#include "Core/Color.hpp"

namespace RayTracer {
    class Cone : public IPrimitive {
        public:
        Cone::Cone(
            const Math::Vector3D &vertex,
            const Math::Vector3D &axis,
            double tangent,
            double maximum,
            double minimum,
            const Color &color
        );

        Intersection intersect(const Ray &ray) const override;

        private:
            Math::Vector3D _vertex;
            Math::Vector3D _axis;
            double _tangent;
            double _maximum;
            double _minimum;
            Color _color;
    };
}