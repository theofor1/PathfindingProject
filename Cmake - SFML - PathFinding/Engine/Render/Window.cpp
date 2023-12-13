#include "Window.h"
#include <System/Input/InputManager.h>
#include <Math/Vector/Vector.h>

Window *Window::instance = nullptr;

// Window::Window() : window(sf::VideoMode::getDesktopMode(), "SFML works!", sf::Style::Fullscreen)
Window::Window(const float _speedMove) : window(sf::VideoMode(1280, 720), "SFML works!"), speedMove(_speedMove)
{
    window.setFramerateLimit(fpsMax);
    window.setSize(sf::Vector2u(Width, Height));
    window.setTitle(Title);

    viewport = sf::View(sf::FloatRect(Width, Height / 2, 500, 500));
    viewport.setSize(window.getSize().x, window.getSize().y);
    viewport.setCenter(window.getSize().x / 2, window.getSize().y / 2);
    window.setView(viewport);

    speedMove = _speedMove;

    InputManager::Instance()->BindOnTriggered(InputAction::Up, [this]()
                                              { axis.y = -1; });
    InputManager::Instance()->BindOnTriggered(InputAction::Down, [this]()
                                              { axis.y = 1; });
    InputManager::Instance()->BindOnTriggered(InputAction::Right, [this]()
                                              { axis.x = 1; });
    InputManager::Instance()->BindOnTriggered(InputAction::Left, [this]()
                                              { axis.x = -1; });
}

sf::RenderWindow &Window::GetWindow()
{
    return window;
}

sf::View &Window::GetView()
{
    return viewport;
}

void Window::UpdateView()
{
    window.setView(viewport);
}

void Window::Update(const float DeltaTime)
{
    window.setView(viewport);

    Vector::Normalized(axis);

    sf::Vector2f velocity = speedMove * axis * DeltaTime;
    viewport.move(velocity);
    UpdateView();
    axis = sf::Vector2f(0, 0);
}

void Window::SetViewSpeedMove(const float _speedMove)
{
    speedMove = _speedMove;
}
