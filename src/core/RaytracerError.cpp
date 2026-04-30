/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** RaytracerError
*/

#include "Core/RaytracerError.hpp"

namespace RayTracer {

RaytracerError::RaytracerError(const std::string &message)
    : _message(message)
{
}

const char *RaytracerError::what() const noexcept
{
    return _message.c_str();
}

}
