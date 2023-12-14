
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
    // std::cout << TextureManager::Instance()->dataXml["PlayerShip"]["Base_Laser"]["SizeY"];
    // std::cout << TextureManager::Instance()->textures["Animation"].getSize().x;

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
