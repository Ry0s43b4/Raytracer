/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Color
*/

#pragma once

#include <algorithm>

namespace RayTracer {

class Color {
public:
    int r;
    int g;
    int b;

    Color() : r(0), g(0), b(0) {}
    Color(int r, int g, int b) : r(r), g(g), b(b) {}

    void clamp()
    {
        r = std::clamp(r, 0, 255);
        g = std::clamp(g, 0, 255);
        b = std::clamp(b, 0, 255);
    }
};

}
