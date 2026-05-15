/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** DLLoader - generic libdl-backed loader for plugin instances
*/

#pragma once

#include <stdexcept>
#include <string>

#include "Plugin/SharedLibrary.hpp"

namespace RayTracer {

class DLLoaderError : public std::runtime_error {
public:
    explicit DLLoaderError(const std::string &what)
        : std::runtime_error(what) {}
};

template <typename T>
class DLLoader {
public:
    using CreateFn = T *(*)();
    using DestroyFn = void (*)(T *);

    DLLoader();
    ~DLLoader() = default;

    DLLoader(const DLLoader &) = delete;
    DLLoader &operator=(const DLLoader &) = delete;

    void open(const std::string &path);
    void close();

    T *createInstance() const;
    void destroyInstance(T *instance) const;

    bool isOpen() const;
    const std::string &path() const noexcept { return _library.path(); }

private:
    SharedLibrary _library;
    CreateFn _create;
    DestroyFn _destroy;
};

template <typename T>
DLLoader<T>::DLLoader()
    : _library(), _create(nullptr), _destroy(nullptr)
{
}

template <typename T>
void DLLoader<T>::open(const std::string &path)
{
    _library.open(path);

    _create = reinterpret_cast<CreateFn>(_library.getSymbol("create"));
    _destroy = reinterpret_cast<DestroyFn>(_library.getSymbol("destroy"));
}

template <typename T>
void DLLoader<T>::close()
{
    _create = nullptr;
    _destroy = nullptr;
    _library.close();
}

template <typename T>
T *DLLoader<T>::createInstance() const
{
    if (_create == nullptr)
        throw DLLoaderError(
            "DLLoader::createInstance called on a closed loader");
    T *instance = _create();
    if (instance == nullptr)
        throw DLLoaderError(
            "Plugin '" + _library.path() + "' returned a null instance");
    return instance;
}

template <typename T>
void DLLoader<T>::destroyInstance(T *instance) const
{
    if (_destroy != nullptr && instance != nullptr)
        _destroy(instance);
}

template <typename T>
bool DLLoader<T>::isOpen() const
{
    return _library.isOpen();
}

}
