#include "IGameManager.h"
#include <System/Input/InputManager.h>
#include <Engine/Render/Window.h>


//#include <Engine/Scene/IScene.h>

#include <Level/Level01.h>
#include <Level/LevelCustom.h>
#include <iostream>

IGameManager* IGameManager::instance = nullptr;

IGameManager::IGameManager()
{
    AddLevel(new Level01());
}

void IGameManager::RunGame()
{
    if (Scenes.size() == 0)
    {
        std::cout << "None Scene";
        exit(EXIT_FAILURE);
    }

    StartActiveScene();

    sf::Clock clock;
    clock.restart();

    while (Window::Instance()->GetWindow().isOpen())
    {
        int deltaTimeMS = clock.getElapsedTime().asMilliseconds();
        float DeltaTime = (float)deltaTimeMS / 1000.f;
        clock.restart();

        sf::Event event;

        while (Window::Instance()->GetWindow().pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                Window::Instance()->GetWindow().close();
            }
        }

        InputManager::Instance()->Update();

        UpdateActiveScene(DeltaTime);

        Window::Instance()->GetWindow().clear();

        DrawActiveScene(Window::Instance()->GetWindow());

        Window::Instance()->GetWindow().display();
    }
}

void IGameManager::AddLevel(IScene* NewScene)
{
    Scenes.push_back(NewScene);
}

IScene* IGameManager::GetActiveScene()
{
    return Scenes[indexActiveScene];
}

void IGameManager::StartActiveScene()
{
    Scenes[indexActiveScene]->Start();
}

void IGameManager::UpdateActiveScene(float DeltaTime)
{
    Scenes[indexActiveScene]->Update(DeltaTime);
}

void IGameManager::DrawActiveScene(sf::RenderWindow& window) const
{
    Scenes[indexActiveScene]->Draw(window);
}
