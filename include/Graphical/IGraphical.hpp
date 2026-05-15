/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** IGraphical - interface every graphical-library plugin must implement
*/

#pragma once

#include <string>

#include "Core/Image.hpp"

namespace RayTracer {

///
/// \brief Abstract interface every graphical library plugin must implement.
///
/// A graphical library is responsible for opening a window, displaying a
/// rendered Image, and handling user events.  Implementations are loaded at
/// runtime through DLLoader<IGraphical> from the ./plugin/ directory.
///
/// Each plugin shared-object must export:
///   - extern "C" RayTracer::IGraphical *create();
///   - extern "C" void destroy(RayTracer::IGraphical *);
///
class IGraphical {
public:
    virtual ~IGraphical() = default;

    virtual std::string name() const = 0;
    virtual void open(int width, int height, const std::string &title) = 0;
    virtual bool isOpen() const = 0;
    virtual bool pollEvents() = 0;
    virtual void display(const Image &image) = 0;
    virtual void close() = 0;
};

}
