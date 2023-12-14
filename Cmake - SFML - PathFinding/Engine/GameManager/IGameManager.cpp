#include "IGameManager.h"
#include <System/Input/InputManager.h>
#include <Engine/Render/Window.h>

// #include <Engine/Scene/IScene.h>

#include <Level/LevelGraph.h>
#include <Level/LevelCustom.h>
#include <iostream>

IGameManager *IGameManager::instance = nullptr;

IGameManager::IGameManager()
{
    AddLevel(new LevelCustom());

    // InputManager::Instance()->BindOnDown(InputAction::Down, [this]()
    //                                { LoadLevel(1); });

    // InputManager::Instance()->BindOnDown(InputAction::Up, [this]()
    //                                { LoadLevel(0); });
    // AddLevel(new LevelGraph());
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

    Window::Instance()->SetViewSpeedMove(500);

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
        Window::Instance()->Update(DeltaTime);

        UpdateActiveScene(DeltaTime);

        Window::Instance()->GetWindow().clear();

        DrawActiveScene(Window::Instance()->GetWindow());

        Window::Instance()->GetView();
        Window::Instance()->GetWindow().display();
    }
}

void IGameManager::LoadLevel(const int LevelIndex)
{
    if (LevelIndex >= Scenes.size())
        return;

    IndexCurrentScene = LevelIndex;
    StartActiveScene();
}

// Private

void IGameManager::AddLevel(IScene *NewScene)
{
    Scenes.push_back(NewScene);
}

IScene *IGameManager::GetActiveScene()
{
    return Scenes[IndexCurrentScene];
}

void IGameManager::StartActiveScene()
{
    if (IndexCurrentScene < 0 || IndexCurrentScene >= Scenes.size())
        return;

    InputManager::Instance()->ResetBind();

    Scenes[IndexCurrentScene]->Start();

    // InputManager::Instance()->Bind(InputAction::Down, [this]()
    //                                { LoadLevel(1); });

    // InputManager::Instance()->Bind(InputAction::Up, [this]()
    //                                { LoadLevel(0); });
}

void IGameManager::UpdateActiveScene(float DeltaTime)
{
    Scenes[IndexCurrentScene]->Update(DeltaTime);
}

void IGameManager::DrawActiveScene(sf::RenderWindow &window) const
{
    Scenes[IndexCurrentScene]->Draw(window);
}
