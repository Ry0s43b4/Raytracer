/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Launcher (SFML 3)
*/

#include "Gui/Launcher.hpp"

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <utility>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Plugin/PluginManager.hpp"

namespace RayTracer {

namespace {

bool loadFallbackFont(sf::Font &font)
{
    static const std::vector<std::string> candidates = {
        "/System/Library/Fonts/Supplemental/Arial.ttf",
        "/System/Library/Fonts/Helvetica.ttc",
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
        "C:\\Windows\\Fonts\\arial.ttf",
    };
    for (const auto &p : candidates) {
        if (std::filesystem::exists(p) && font.openFromFile(p))
            return true;
    }
    return false;
}

std::vector<std::string> listScenes(const std::string &dir)
{
    std::vector<std::string> result;
    namespace fs = std::filesystem;
    if (!fs::exists(dir) || !fs::is_directory(dir))
        return result;
    for (const auto &entry : fs::directory_iterator(dir)) {
        if (!entry.is_regular_file())
            continue;
        const auto ext = entry.path().extension().string();
        if (ext == ".cfg" || ext == ".txt")
            result.push_back(entry.path().string());
    }
    std::sort(result.begin(), result.end());
    return result;
}

struct Button {
    sf::FloatRect bounds {{0.f, 0.f}, {0.f, 0.f}};
    std::string label;
    bool selected = false;
};

void drawButton(sf::RenderWindow &win, const Button &b, const sf::Font &font,
    bool hasFont)
{
    sf::RectangleShape shape(b.bounds.size);
    shape.setPosition(b.bounds.position);
    if (b.selected) {
        shape.setFillColor(sf::Color(80, 130, 200));
        shape.setOutlineColor(sf::Color::White);
    } else {
        shape.setFillColor(sf::Color(60, 60, 70));
        shape.setOutlineColor(sf::Color(120, 120, 130));
    }
    shape.setOutlineThickness(2.f);
    win.draw(shape);

    if (hasFont) {
        sf::Text text(font, b.label, 16);
        text.setFillColor(sf::Color::White);
        const auto rect = text.getLocalBounds();
        text.setPosition({
            b.bounds.position.x + 12.f,
            b.bounds.position.y
                + (b.bounds.size.y - rect.size.y) / 2.f - 4.f
        });
        win.draw(text);
    }
}

void drawLabel(sf::RenderWindow &win, const std::string &s, float x, float y,
    unsigned size, const sf::Font &font, bool hasFont,
    sf::Color color = sf::Color::White)
{
    if (!hasFont)
        return;
    sf::Text t(font, s, size);
    t.setFillColor(color);
    t.setPosition({x, y});
    win.draw(t);
}

}

Launcher::Launcher(std::string scenesDir, std::string pluginsDir)
    : _scenesDir(std::move(scenesDir)), _pluginsDir(std::move(pluginsDir))
{}

LauncherChoice Launcher::run()
{
    LauncherChoice choice;

    PluginManager plugins(_pluginsDir);
    auto scenes = listScenes(_scenesDir);

    constexpr unsigned WIN_W = 800;
    constexpr unsigned WIN_H = 600;
    sf::RenderWindow window(
        sf::VideoMode(sf::Vector2u(WIN_W, WIN_H)),
        "Raytracer - Launcher",
        sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    sf::Font font;
    const bool hasFont = loadFallbackFont(font);
    if (!hasFont) {
        std::cerr <<
            "Warning: no system font found, GUI will be drawn without text.\n";
    }

    std::vector<Button> sceneButtons;
    sceneButtons.reserve(scenes.size());
    for (size_t i = 0; i < scenes.size(); ++i) {
        Button b;
        b.bounds = sf::FloatRect({40.f, 90.f + i * 38.f}, {340.f, 32.f});
        b.label = std::filesystem::path(scenes[i]).filename().string();
        sceneButtons.push_back(b);
    }
    if (!sceneButtons.empty())
        sceneButtons.front().selected = true;

    std::vector<Button> pluginButtons;
    pluginButtons.reserve(plugins.plugins().size());
    for (size_t i = 0; i < plugins.plugins().size(); ++i) {
        Button b;
        b.bounds = sf::FloatRect({420.f, 90.f + i * 38.f}, {340.f, 32.f});
        b.label = plugins.plugins()[i].name();
        pluginButtons.push_back(b);
    }
    if (!pluginButtons.empty())
        pluginButtons.front().selected = true;

    Button startBtn;
    startBtn.bounds = sf::FloatRect(
        {WIN_W / 2.f - 80.f, WIN_H - 70.f},
        {160.f, 44.f});
    startBtn.label = "Start";
    startBtn.selected = true;

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            } else if (auto *kp = event->getIf<sf::Event::KeyPressed>()) {
                if (kp->code == sf::Keyboard::Key::Escape)
                    window.close();
            } else if (auto *mb =
                       event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mb->button != sf::Mouse::Button::Left)
                    continue;
                const sf::Vector2f m{
                    static_cast<float>(mb->position.x),
                    static_cast<float>(mb->position.y)};

                for (auto &b : sceneButtons) {
                    if (b.bounds.contains(m)) {
                        for (auto &x : sceneButtons) x.selected = false;
                        b.selected = true;
                    }
                }
                for (auto &b : pluginButtons) {
                    if (b.bounds.contains(m)) {
                        for (auto &x : pluginButtons) x.selected = false;
                        b.selected = true;
                    }
                }
                if (startBtn.bounds.contains(m)
                    && !sceneButtons.empty() && !pluginButtons.empty()) {
                    for (size_t i = 0; i < sceneButtons.size(); ++i) {
                        if (sceneButtons[i].selected) {
                            choice.scenePath = scenes[i];
                            break;
                        }
                    }
                    for (size_t i = 0; i < pluginButtons.size(); ++i) {
                        if (pluginButtons[i].selected) {
                            choice.pluginPath = plugins.plugins()[i].path();
                            choice.pluginName = plugins.plugins()[i].name();
                            break;
                        }
                    }
                    choice.startRequested = true;
                    window.close();
                }
            }
        }

        window.clear(sf::Color(30, 30, 40));

        drawLabel(window, "Raytracer launcher", 40.f, 28.f, 24, font, hasFont);
        drawLabel(window, "Scene", 40.f, 64.f, 18, font, hasFont,
            sf::Color(180, 180, 200));
        drawLabel(window, "Display plugin", 420.f, 64.f, 18, font, hasFont,
            sf::Color(180, 180, 200));

        if (sceneButtons.empty()) {
            drawLabel(window,
                "No scene files found in " + _scenesDir,
                40.f, 90.f, 14, font, hasFont, sf::Color(220, 100, 100));
        }
        if (pluginButtons.empty()) {
            drawLabel(window,
                "No plugins found in " + _pluginsDir,
                420.f, 90.f, 14, font, hasFont, sf::Color(220, 100, 100));
        }

        for (const auto &b : sceneButtons)
            drawButton(window, b, font, hasFont);
        for (const auto &b : pluginButtons)
            drawButton(window, b, font, hasFont);
        drawButton(window, startBtn, font, hasFont);

        drawLabel(window,
            "Esc: quit   |   Click to select   |   Start to render",
            40.f, WIN_H - 28.f, 14, font, hasFont, sf::Color(160, 160, 170));

        window.display();
    }

    return choice;
}

}
