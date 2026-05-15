/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** SFMLDisplay (SFML 3)
*/

#include "SFMLDisplay.hpp"

#include <algorithm>
#include <cstdint>
#include <vector>

namespace RayTracer {

SFMLDisplay::SFMLDisplay()
    : _window(nullptr), _texture(), _sprite(std::nullopt),
      _width(0), _height(0)
{}

SFMLDisplay::~SFMLDisplay()
{
    close();
}

std::string SFMLDisplay::name() const
{
    return "SFML Display";
}

void SFMLDisplay::open(int width, int height, const std::string &title)
{
    _width = width;
    _height = height;

    const sf::Vector2u size(static_cast<unsigned>(width),
                            static_cast<unsigned>(height));

    _window = std::make_unique<sf::RenderWindow>(
        sf::VideoMode(size),
        title,
        sf::Style::Titlebar | sf::Style::Close);
    _window->setFramerateLimit(60);

    (void)_texture.resize(size);
    _sprite.emplace(_texture);
}

bool SFMLDisplay::isOpen() const
{
    return _window && _window->isOpen();
}

bool SFMLDisplay::pollEvents()
{
    if (!_window || !_window->isOpen())
        return false;

    while (auto event = _window->pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            _window->close();
            return false;
        }
        if (auto *kp = event->getIf<sf::Event::KeyPressed>()) {
            if (kp->code == sf::Keyboard::Key::Escape
                || kp->code == sf::Keyboard::Key::Q) {
                _window->close();
                return false;
            }
        }
    }
    return true;
}

void SFMLDisplay::display(const Image &image)
{
    if (!_window || !_window->isOpen())
        return;

    const int w = image.width();
    const int h = image.height();
    if (w != _width || h != _height) {
        _width = w;
        _height = h;
        const sf::Vector2u size(static_cast<unsigned>(w),
                                static_cast<unsigned>(h));
        (void)_texture.resize(size);
        _sprite.emplace(_texture);
    } else if (!_sprite) {
        _sprite.emplace(_texture);
    }

    std::vector<std::uint8_t> pixels(static_cast<size_t>(w) * h * 4);
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            const Color &c = image.getPixel(x, y);
            const size_t i = (static_cast<size_t>(y) * w + x) * 4;
            pixels[i + 0] = static_cast<std::uint8_t>(std::clamp(c.r, 0, 255));
            pixels[i + 1] = static_cast<std::uint8_t>(std::clamp(c.g, 0, 255));
            pixels[i + 2] = static_cast<std::uint8_t>(std::clamp(c.b, 0, 255));
            pixels[i + 3] = 255;
        }
    }
    _texture.update(pixels.data());

    _window->clear(sf::Color::Black);
    if (_sprite)
        _window->draw(*_sprite);
    _window->display();
}

void SFMLDisplay::close()
{
    _sprite.reset();
    if (_window) {
        if (_window->isOpen())
            _window->close();
        _window.reset();
    }
}

}

extern "C" RayTracer::IGraphical *create()
{
    return new RayTracer::SFMLDisplay();
}

extern "C" void destroy(RayTracer::IGraphical *plugin)
{
    delete plugin;
}
