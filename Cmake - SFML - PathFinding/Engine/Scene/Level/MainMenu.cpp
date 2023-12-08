#include "MainMenu.h"
#include <iostream>
#include <System/Input/InputManager.h>

MainMenu::MainMenu() {
	InputManager::Instance()->Bind(InputAction::Right, [this]() 
		{ std::cout << "Right\n"; });
	InputManager::Instance()->Bind(InputAction::Left, [this]()
		{ std::cout << "Left\n"; });
	/*InputManager::Instance()->Bind(InputAction::MouseL, [this]()
		{ std::cout << "Click\n"; });*/
}

void MainMenu::Start()
{
	IScene::Start();
	
	if (!font.loadFromFile("./Ressources/Fonts/PixelFont.ttf")) {
		std::cout << "Failed to load font";
	} 
	else 
	{
		std::cout << "load font";
	}

	text.setFont(font); // Définition de la police de caractères
	text.setString("Bonjour, SFML !"); // Définition du texte
	text.setCharacterSize(24); // Taille des caractères
	text.setFillColor(sf::Color::White); // Couleur du texte
}

void MainMenu::Update(float DeltaTime)
{
	IScene::Update(DeltaTime);

	
}

void MainMenu::Destroy()
{
	IScene::Destroy();

}

void MainMenu::Draw(sf::RenderWindow& window) const
{
	IScene::Draw(window);

	
}