#include "Window.h"

Window* Window::instance = nullptr;

// Window::Window() : window(sf::VideoMode::getDesktopMode(), "SFML works!", sf::Style::Fullscreen)
Window::Window() : window(sf::VideoMode(1280, 720), "SFML works!")
{
    window.setFramerateLimit(fpsMax);
    window.setSize(sf::Vector2u(Width, Height));
    window.setTitle(Title);
}

sf::RenderWindow& Window::GetWindow()
{
    return window;
}
