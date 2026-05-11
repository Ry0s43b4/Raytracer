/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** PluginManager
*/

#include "Plugin/PluginManager.hpp"

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <utility>

namespace RayTracer {

PluginEntry::PluginEntry(std::string path, std::string name,
    std::shared_ptr<Loader> loader)
    : _path(std::move(path)), _name(std::move(name)),
      _loader(std::move(loader))
{}

PluginEntry::Instance PluginEntry::instantiate() const
{
    IGraphical *raw = _loader->createInstance();
    auto loader = _loader;
    auto deleter = [loader](IGraphical *p) {
        if (p)
            loader->destroyInstance(p);
    };
    return Instance(raw, deleter);
}

namespace {

bool hasPluginExtension(const std::filesystem::path &p)
{
    const auto ext = p.extension().string();
    return ext == ".so" || ext == ".dylib";
}

}

PluginManager::PluginManager(const std::string &directory)
{
    namespace fs = std::filesystem;

    if (!fs::exists(directory) || !fs::is_directory(directory))
        return;

    std::vector<fs::path> candidates;
    for (const auto &entry : fs::directory_iterator(directory)) {
        if (entry.is_regular_file() && hasPluginExtension(entry.path()))
            candidates.push_back(entry.path());
    }
    std::sort(candidates.begin(), candidates.end());

    for (const auto &path : candidates) {
        try {
            auto loader = std::make_shared<DLLoader<IGraphical>>();
            loader->open(path.string());

            std::string pluginName = path.stem().string();
            try {
                IGraphical *probe = loader->createInstance();
                if (probe != nullptr) {
                    pluginName = probe->name();
                    loader->destroyInstance(probe);
                }
            } catch (const std::exception &probeErr) {
                std::cerr << "Warning: could not probe '" << path
                    << "': " << probeErr.what() << "\n";
            }

            _plugins.emplace_back(path.string(), pluginName, loader);
        } catch (const std::exception &e) {
            std::cerr << "Skipping '" << path << "': " << e.what() << "\n";
        }
    }
}

}
