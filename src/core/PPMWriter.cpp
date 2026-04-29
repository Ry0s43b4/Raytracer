/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** PPMWriter
*/

#include <fstream>

#include "core/PPMWriter.hpp"
#include "core/RaytracerError.hpp"

namespace RayTracer {

void PPMWriter::save(const Image &image, const std::string &filepath)
{
    std::ofstream file(filepath);

    if (!file.is_open())
        throw RaytracerError("Cannot open output file: " + filepath);

    file << "P3\n";
    file << image.width() << " " << image.height() << "\n";
    file << "255\n";

    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            Color color = image.getPixel(x, y);
            color.clamp();

            file << color.r << " "
                 << color.g << " "
                 << color.b << "\n";
        }
    }

    if (!file.good())
        throw RaytracerError("Failed while writing output file: " + filepath);
}

}
