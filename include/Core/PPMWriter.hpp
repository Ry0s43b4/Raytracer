/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** PPMWriter
*/

#pragma once

#include <string>
#include "core/Image.hpp"

namespace RayTracer {

class PPMWriter {
public:
    static void save(const Image &image, const std::string &filepath);
};

}
