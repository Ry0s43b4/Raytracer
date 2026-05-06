/*
** EPITECH PROJECT, 2026
** G-OOP-400-PAR-4-1-raytracer-22
** File description:
** Point3D
*/

#pragma once

namespace Math {
    class Point3D {
        public:
            int x;
            int y;
            int z;
        
            Point3D() = default;
            Point3D(int x, int y, int z) : x(x), y(y), z(z) {}
            ~Point3D() = default;
    };   
}