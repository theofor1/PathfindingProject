#include "Window.h"

Window* Window::instance = nullptr;

Window::Window() : window(sf::VideoMode(1280, 720), "SFML works!")
{
    window.setFramerateLimit(fpsMax);
}

sf::RenderWindow& Window::GetWindow()
{
    return window;
}
