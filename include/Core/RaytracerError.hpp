/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** RaytracerError
*/

#pragma once

#include <exception>
#include <string>

namespace RayTracer {

class RaytracerError : public std::exception {
public:
    explicit RaytracerError(const std::string &message);

    const char *what() const noexcept override;

private:
    std::string _message;
};

}
