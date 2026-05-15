/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** SharedLibrary
*/

#include "Plugin/SharedLibrary.hpp"

#include <dlfcn.h>

namespace RayTracer {

SharedLibrary::SharedLibrary()
    : _handle(nullptr), _path()
{}

SharedLibrary::~SharedLibrary()
{
    close();
}

void SharedLibrary::open(const std::string &path)
{
    if (_handle != nullptr)
        close();

    void *handle = ::dlopen(path.c_str(), RTLD_NOW | RTLD_LOCAL);
    if (handle == nullptr) {
        const char *err = ::dlerror();
        throw SharedLibraryError(
            "Failed to open shared object '" + path + "': "
            + (err ? err : "unknown error"));
    }
    _handle = handle;
    _path = path;
}

void SharedLibrary::close()
{
    if (_handle != nullptr) {
        ::dlclose(_handle);
        _handle = nullptr;
    }
    _path.clear();
}

bool SharedLibrary::isOpen() const noexcept
{
    return _handle != nullptr;
}

void *SharedLibrary::getSymbol(const std::string &symbol) const
{
    if (_handle == nullptr)
        throw SharedLibraryError(
            "Cannot lookup symbol '" + symbol + "': no library loaded");

    ::dlerror();
    void *sym = ::dlsym(_handle, symbol.c_str());
    const char *err = ::dlerror();
    if (err != nullptr) {
        throw SharedLibraryError(
            "Failed to load symbol '" + symbol + "' from '" + _path + "': "
            + err);
    }
    return sym;
}

}
