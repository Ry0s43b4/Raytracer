/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Image
*/

#pragma once

#include <vector>
#include "core/Color.hpp"

namespace RayTracer {

class Image {
public:
    Image(int width, int height);

    int width() const;
    int height() const;

    void setPixel(int x, int y, const Color &color);
    const Color &getPixel(int x, int y) const;

private:
    int _width;
    int _height;
    std::vector<Color> _pixels;

    int index(int x, int y) const;
};

}
