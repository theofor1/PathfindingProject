
#include <Engine/GameManager/IGameManager.h>
#include <Engine/Render/Ressource/TextureManager.h>
#include <Engine/System/Input/InputManager.h>
#include <Engine/System/Input/InputManager.h>
#include <Engine/Render/Window.h>

void TextureManager()
{
    TextureManager::Instance()->ExtractFileData("./Ressources/PlayerShip/PlayerShip.xml");
}

void RunGame()
{
    IGameManager::Instance()->RunGame();
}

int main()
{
    TextureManager();

    RunGame();

    // Destroy Instances
    {
        IGameManager::DeleteInstance();
        TextureManager::DeleteInstance();
        InputManager::DeleteInstance();
        Window::DeleteInstance();
    }

    return 0;
}
