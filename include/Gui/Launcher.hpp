/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Launcher - SFML-based GUI to pick a scene file and a display plugin
*/

#pragma once

#include <string>
#include <vector>

#include "Plugin/PluginManager.hpp"

namespace RayTracer {

///
/// \brief What the user selected in the launcher.
///
struct LauncherChoice {
    bool startRequested = false;
    std::string scenePath;
    std::string pluginPath;
    std::string pluginName;
};

///
/// \brief SFML-based launcher window.
///
/// Lets the user pick:
///   - a configuration file (scanned from ./scenes/, *.cfg / *.txt)
///   - a graphical plugin (loaded from ./plugin/ via libdl)
/// then click "Start".
///
class Launcher {
public:
    Launcher(std::string scenesDir = "./scenes",
             std::string pluginsDir = "./plugin");

    LauncherChoice run();

private:
    std::string _scenesDir;
    std::string _pluginsDir;
};

}
