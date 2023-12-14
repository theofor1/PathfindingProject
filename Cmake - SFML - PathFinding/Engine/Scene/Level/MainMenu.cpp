#include "MainMenu.h"
#include <iostream>
#include <System/Input/InputManager.h>
#include <Engine/Render/Window.h>
#include <GameManager/IGameManager.h>

MainMenu::MainMenu()
{
}

void MainMenu::Start()
{
	IScene::Start();

	ColorOnSelected = sf::Color(0, 0, 255);

	outerBox = new UIElement(sf::Vector2f(0.5f, 0.f), sf::Vector2f(0.1f, 0.3f));
	outerBox->SetLayout(UILayout::List, UIDirection::Vertical);

	title = new Text(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.5f, 0.1f));
	title->text.setString("Space seeker");
	outerBox->AddChild(title);

	btnPlay = new Button(sf::Vector2f(0.f, 0.0f), sf::Vector2f(0.5f, 0.1f));
	btnPlay->TextButton.setString("Play");
	outerBox->AddChild(btnPlay);

	btnExit = new Button(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.5f, 0.1f));
	btnExit->TextButton.setString("Exit");
	outerBox->AddChild(btnExit);

	outerBox->Start();

	// INPUT BINDING

	InputManager::Instance()->BindOnDown(InputAction::MouseL, [this]()
										 { OnButtonsClick(); });

	if (!font.loadFromFile("./Ressources/Fonts/OpenSans-Regular.ttf"))
	{
		std::cout << "Failed to load font";
	}

	text.setFont(font);					 // D�finition de la police de caract�res
	text.setString("Bonjour, SFML !");	 // D�finition du texte
	text.setCharacterSize(24);			 // Taille des caract�res
	text.setFillColor(sf::Color::White); // Couleur du texte
}

void MainMenu::Update(float DeltaTime)
{
	IScene::Update(DeltaTime);

	sf::View viewport = Window::Instance()->GetView();
	sf::FloatRect windowRect(viewport.getCenter().x - viewport.getSize().x / 2, viewport.getCenter().y - viewport.getSize().y / 2, viewport.getSize().x, viewport.getSize().y);
	outerBox->UpdateRect(windowRect);
	outerBox->Update(DeltaTime);
}

void MainMenu::Destroy()
{
	IScene::Destroy();
}

void MainMenu::Draw(sf::RenderWindow &window) const
{
	IScene::Draw(window);
	sf::Vector2u windowSize = window.getSize();
	sf::FloatRect windowRect(0, 0, windowSize.x, windowSize.y);
	outerBox->UpdateRect(windowRect);
	outerBox->Draw(window);
}

void MainMenu::OnButtonsClick()
{
	sf::Vector2i MouseLocation = sf::Mouse::getPosition(Window::Instance()->GetWindow());
	sf::Vector2f WorldMouseLocation = Window::Instance()->GetWindow().mapPixelToCoords(MouseLocation);

	if (btnPlay->Clicked(WorldMouseLocation))
	{
		IGameManager::Instance()->LoadLevel(1);
		return;
	}

	if (btnExit->Clicked(WorldMouseLocation))
	{
		exit(0);
		return;
	}
}