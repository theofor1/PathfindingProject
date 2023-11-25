#include "IGameManager.h"
// #include <map>
#include <Engine/Render/Window.h>
#include <iostream>
// #include <Level/Level01.h>
#include <System/Input/InputManager.h>
#include <Actor/Actor.h>
// #include <Actor/PlayerShip/PlayerShip.h>
#include <Engine/Scene/IScene.h>


IGameManager* IGameManager::instance = nullptr;

IGameManager::IGameManager()
{
    // AddLevel(Level01());
}

void IGameManager::RunGame()
{
    // if (Scenes.size() == 0)
    // {
    //     std::cout << "None Scene";
    //     exit(EXIT_FAILURE);
    // }

    // StartActiveScene();

    // sf::Clock clock;
    // clock.restart();
   
    // while (Window::Instance()->GetWindow().isOpen())
    // {
    //     int deltaTimeMS = clock.getElapsedTime().asMilliseconds();
    //     float FDeltaTimeS = (float)deltaTimeMS / 1000.f;
    //     clock.restart();

    //     sf::Event event;

    //     while (Window::Instance()->GetWindow().pollEvent(event))
    //     {
    //         if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    //         {
    //             Window::Instance()->GetWindow().close();
    //         }
    //     }

    //     // InputManager::Instance()->Update();

    //     // UpdateActiveScene(FDeltaTimeS);

    //     // Window::Instance()->GetWindow().clear();

    //     // DrawActiveScene(Window::Instance()->GetWindow());

    //     //
    //     // GameObject* g = Scenes[indexActiveScene].GetGameObjects()[0];

    //     // if (static_cast<Actor*>(g))
    //     // {
    //     //     Actor* a = static_cast<Actor*>(g);

    //     //     if (static_cast<PlayerShip*>(a))
    //     //     {
    //     //         PlayerShip* ps = static_cast<PlayerShip*>(a);
    //     //         //ps->curve.Draw(Window::Instance()->GetWindow());
    //     //     }
    //     // }
    //     //

    //     Window::Instance()->GetWindow().display();
    // }
}

void IGameManager::AddLevel(IScene NewScene)
{
    Scenes.push_back(NewScene);
}

IScene& IGameManager::GetActiveScene()
{
    return Scenes[indexActiveScene];
}

void IGameManager::StartActiveScene()
{
    // Scenes[indexActiveScene].Start();
}

void IGameManager::UpdateActiveScene(float fDeltaTime)
{
    // Scenes[indexActiveScene].Update(fDeltaTime);
    // Scenes[indexActiveScene].OnCollision();
}

void IGameManager::DrawActiveScene(sf::RenderWindow& window) const
{
    // Scenes[indexActiveScene].Draw(window);
}



