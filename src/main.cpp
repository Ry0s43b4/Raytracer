/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** main
*/

#include <iostream>
#include <memory>
#include <string>

#include "Core/RaytracerError.hpp"
#include "Core/Renderer.hpp"
#include "Core/PPMWriter.hpp"
#include "Scene/SceneParser.hpp"
#include "Scene/SceneBuilder.hpp"

#include "Graphical/IGraphical.hpp"
#include "Gui/Launcher.hpp"
#include "Plugin/DLLoader.hpp"

static void printUsage()
{
    std::cout << "USAGE: ./raytracer [SCENE_FILE | --gui]\n";
    std::cout << "  SCENE_FILE : scene configuration (writes output.ppm)\n";
    std::cout << "  --gui      : launch the SFML graphical launcher\n";
    std::cout << "  no args    : same as --gui\n";
}

namespace {

int runHeadless(const std::string &scenePath)
{
    RayTracer::SceneParser parser(scenePath);
    RayTracer::SceneData data = parser.parse();

    RayTracer::SceneBuilder builder;
    RayTracer::Scene scene = builder.build(data);

    RayTracer::Renderer renderer;
    RayTracer::Image image = renderer.render(scene);

    RayTracer::PPMWriter::save(image, "output.ppm");
    std::cout << "Rendered successfully to output.ppm" << std::endl;
    return 0;
}

int runWithPlugin(const std::string &scenePath,
                  const std::string &pluginPath,
                  const std::string &pluginName)
{
    RayTracer::SceneParser parser(scenePath);
    RayTracer::SceneData data = parser.parse();

    RayTracer::SceneBuilder builder;
    RayTracer::Scene scene = builder.build(data);

    RayTracer::Renderer renderer;
    RayTracer::Image image = renderer.render(scene);

    RayTracer::PPMWriter::save(image, "output.ppm");

    RayTracer::DLLoader<RayTracer::IGraphical> loader;
    loader.open(pluginPath);

    RayTracer::IGraphical *raw = loader.createInstance();
    auto deleter = [&loader](RayTracer::IGraphical *p) {
        loader.destroyInstance(p);
    };
    std::unique_ptr<RayTracer::IGraphical, decltype(deleter)>
        plugin(raw, deleter);

    plugin->open(image.width(), image.height(),
        "Raytracer - " + pluginName);
    plugin->display(image);

    while (plugin->isOpen() && plugin->pollEvents()) {
        plugin->display(image);
    }
    plugin->close();
    return 0;
}

int runGui()
{
    RayTracer::Launcher launcher;
    auto choice = launcher.run();
    if (!choice.startRequested) {
        std::cout << "Launcher closed without starting a render." << std::endl;
        return 0;
    }
    return runWithPlugin(choice.scenePath, choice.pluginPath,
        choice.pluginName);
}

}

int main(int ac, char **av)
{
    try {
        if (ac == 1)
            return runGui();

        const std::string arg1 = av[1];
        if (arg1 == "--help" || arg1 == "-h") {
            printUsage();
            return 0;
        }
        if (arg1 == "--gui")
            return runGui();
        if (ac == 2)
            return runHeadless(arg1);

        printUsage();
        return 84;
    } catch (const RayTracer::RaytracerError &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    } catch (const std::exception &e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
        return 84;
    }
}
