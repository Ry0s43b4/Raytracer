/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Image
*/

#include "core/Image.hpp"
#include "core/RaytracerError.hpp"

namespace RayTracer {

Image::Image(int width, int height)
    : _width(width), _height(height), _pixels(width * height)
{
    if (width <= 0 || height <= 0)
        throw RaytracerError("Image dimensions must be positive");
}

int Image::width() const
{
    return _width;
}

int Image::height() const
{
    return _height;
}

void Image::setPixel(int x, int y, const Color &color)
{
    _pixels[index(x, y)] = color;
}

const Color &Image::getPixel(int x, int y) const
{
    return _pixels[index(x, y)];
}

int Image::index(int x, int y) const
{
    if (x < 0 || x >= _width || y < 0 || y >= _height)
        throw RaytracerError("Pixel coordinates out of image bounds");
    return y * _width + x;
}

}
