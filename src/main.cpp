/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** main
*/

#include <iostream>
#include <string>

#include "Core/RaytracerError.hpp"
#include "Core/Renderer.hpp"
#include "Core/PPMWriter.hpp"
#include "Scene/SceneParser.hpp"
#include "Scene/SceneBuilder.hpp"

static void printUsage()
{
    std::cout << "USAGE: ./raytracer <SCENE_FILE>\n";
    std::cout << "  SCENE_FILE: scene configuration\n";
}

int main(int ac, char **av)
{
    try {
        if (ac != 2) {
            printUsage();
            return 84;
        }

        std::string filepath = av[1];

        if (filepath == "--help") {
            printUsage();
            return 0;
        }

        RayTracer::SceneParser parser(filepath);
        RayTracer::SceneData data = parser.parse();

        RayTracer::SceneBuilder builder;
        RayTracer::Scene scene = builder.build(data);

        RayTracer::Renderer renderer;
        RayTracer::Image image = renderer.render(scene);

        RayTracer::PPMWriter::save(image, "output.ppm");

        std::cout << "Rendered successfully to output.ppm" << std::endl;

    } catch (const RayTracer::RaytracerError &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    } catch (const std::exception &e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
        return 84;
    }

    return 0;
}
