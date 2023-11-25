
#include <Engine/GameManager/IGameManager.h>
#include <Engine/Render/Ressource/TextureManager.h>
#include <Engine/System/Input/InputManager.h>

#include <iostream>

int main()
{

    // std::ifstream file("Resources/PlayerShip/PlayerShip.xml");

    // Texture Manager
    {
       TextureManager::Instance()->ExtractFileData("./Ressources/PlayerShip/PlayerShip.xml");
        // TextureManager::Instance()->ExtractFileData("./Ressources/Weapons/Laser.xml");
        // TextureManager::Instance()->ExtractFileData("./Ressources/Ennemies/Alien.xml");

        //
        // TextureManager::Instance()->ExtractFileData("./Ressources/Basement.xml");
        // TextureManager::Instance()->ExtractFileData("./Ressources/Tear.xml");
    }

    // std::cout << TextureManager::Instance()->dataXml["PlayerShip"]["Base_Laser"]["SizeY"];
    // std::cout << TextureManager::Instance()->textures["Animation"].getSize().x;

    // GAME MANAGER
    {
        IGameManager::Instance()->RunGame();
    }

    // Destroy Instances
    {
        IGameManager::DeleteInstance();
        TextureManager::DeleteInstance();
    }
    return 0;
}
