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

    static Color scale(const Color &c, double s);
    static Color multiply(const Color &a, const Color &b);
    static Color add(const Color &a, const Color &b);
    /// Linear blend: \p a when t = 0, \p b when t = 1.
    static Color blend(const Color &a, const Color &b, double t);

    void clamp()
    {
        r = std::clamp(r, 0, 255);
        g = std::clamp(g, 0, 255);
        b = std::clamp(b, 0, 255);
    }
};

inline Color Color::scale(const Color &c, double s)
{
    auto ch = [](int v, double k) {
        return static_cast<int>(std::clamp(static_cast<int>(v * k), 0, 255));
    };

    return Color(ch(c.r, s), ch(c.g, s), ch(c.b, s));
}

inline Color Color::multiply(const Color &a, const Color &b)
{
    return Color(
        static_cast<int>(std::clamp((a.r * b.r) / 255, 0, 255)),
        static_cast<int>(std::clamp((a.g * b.g) / 255, 0, 255)),
        static_cast<int>(std::clamp((a.b * b.b) / 255, 0, 255))
    );
}

inline Color Color::add(const Color &a, const Color &b)
{
    Color o(a.r + b.r, a.g + b.g, a.b + b.b);

    o.clamp();
    return o;
}

inline Color Color::blend(const Color &a, const Color &b, double t)
{
    t = std::clamp(t, 0.0, 1.0);
    return add(scale(a, 1.0 - t), scale(b, t));
}

}
