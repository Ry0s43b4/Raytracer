/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** SFMLDisplay - SFML 3 implementation of IGraphical
*/

#pragma once

#include <memory>
#include <optional>
#include <string>

#include <SFML/Graphics.hpp>

#include "Graphical/IGraphical.hpp"

namespace RayTracer {

class SFMLDisplay : public IGraphical {
public:
    SFMLDisplay();
    ~SFMLDisplay() override;

    std::string name() const override;

    void open(int width, int height, const std::string &title) override;
    bool isOpen() const override;
    bool pollEvents() override;
    void display(const Image &image) override;
    void close() override;

private:
    std::unique_ptr<sf::RenderWindow> _window;
    sf::Texture _texture;
    std::optional<sf::Sprite> _sprite;
    int _width;
    int _height;
};

}
