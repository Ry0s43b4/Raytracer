/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** main
*/

#include <iostream>
#include <string>

#include "Core/RaytracerError.hpp"

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

        // TODO:
        // SceneParser parser(filepath);
        // Scene scene = parser.parse();
        // Renderer renderer;
        // Image image = renderer.render(scene);
        // PPMWriter::save(image, "output.ppm");

        std::cout << "Core initialized. Ready for rendering pipeline." << std::endl;

    } catch (const RayTracer::RaytracerError &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    } catch (const std::exception &e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
        return 84;
    }

    return 0;
}
