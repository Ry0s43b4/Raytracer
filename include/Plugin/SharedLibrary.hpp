/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** SharedLibrary - thin RAII wrapper around libdl
*/

#pragma once

#include <stdexcept>
#include <string>

namespace RayTracer {

///
/// \brief Error thrown by SharedLibrary on dlopen / dlsym failures.
///
class SharedLibraryError : public std::runtime_error {
public:
    explicit SharedLibraryError(const std::string &what)
        : std::runtime_error(what) {}
};

///
/// \brief RAII handle on a shared object loaded with libdl.
///
/// SharedLibrary is the low-level primitive. It owns the dlopen handle and
/// exposes a typed-pointer symbol lookup. It is non-copyable and non-movable
/// to keep ownership unambiguous.
///
/// Higher-level loaders (e.g. DLLoader<T>) compose a SharedLibrary as a
/// member.
///
class SharedLibrary {
public:
    SharedLibrary();
    ~SharedLibrary();

    SharedLibrary(const SharedLibrary &) = delete;
    SharedLibrary &operator=(const SharedLibrary &) = delete;
    SharedLibrary(SharedLibrary &&) = delete;
    SharedLibrary &operator=(SharedLibrary &&) = delete;

    void open(const std::string &path);
    void close();
    bool isOpen() const noexcept;

    const std::string &path() const noexcept { return _path; }
    void *getSymbol(const std::string &symbol) const;

private:
    void *_handle;
    std::string _path;
};

}
