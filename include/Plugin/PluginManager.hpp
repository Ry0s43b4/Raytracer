/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** PluginManager - discovers graphical-library plugins under ./plugin/
*/

#pragma once

#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "Graphical/IGraphical.hpp"
#include "Plugin/DLLoader.hpp"

namespace RayTracer {

///
/// \brief A reference to a graphical plugin discovered on disk.
///
/// The library is loaded eagerly so the plugin's display name can be queried
/// for the launcher GUI. instantiate() builds a fresh instance and returns it
/// in a unique_ptr whose deleter calls back into the plugin's destroy()
/// symbol.
///
class PluginEntry {
public:
    using Loader = DLLoader<IGraphical>;
    using Instance = std::unique_ptr<IGraphical,
        std::function<void(IGraphical *)>>;

    PluginEntry(std::string path, std::string name,
        std::shared_ptr<Loader> loader);

    const std::string &path() const noexcept { return _path; }
    const std::string &name() const noexcept { return _name; }

    Instance instantiate() const;

private:
    std::string _path;
    std::string _name;
    std::shared_ptr<Loader> _loader;
};

///
/// \brief Scans a directory for plugin shared objects and exposes them.
///
class PluginManager {
public:
    /// Scan \p directory for *.so / *.dylib files. Files that don't expose
    /// the create/destroy symbols are silently skipped (with a warning on
    /// stderr).
    explicit PluginManager(const std::string &directory = "./plugin");

    const std::vector<PluginEntry> &plugins() const noexcept { return _plugins; }

private:
    std::vector<PluginEntry> _plugins;
};

}
