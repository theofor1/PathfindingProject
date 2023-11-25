#include "Renderer.h"
#include <Engine/Render/Drawable/IDrawable.h>
#include <GameObject/GameObject.h>
#include <Component/Transform/Transform.h>
#include <SFML/Graphics/RenderWindow.hpp>

Renderer::Renderer(GameObject& gameObject) : IComponent(gameObject)
{}

void Renderer::Start()
{
}

void Renderer::Update(float DeltaTime)
{
	for (auto & Drawable : Drawables)
	{
		// Set Drawable transform with parent transform
		Drawable->SetWorldTransform(GetGameObject().GetComponent<Transform>()->GetTransform(), GetGameObject().GetComponent<Transform>()->GetOffsetPosition());
		Drawable->Update(DeltaTime);
	}
}

void Renderer::Destroy()
{
}

std::string Renderer::GetComponentName() const
{
	return "Renderer";
}

void Renderer::Draw(sf::RenderWindow& window) const
{
	for (auto& Drawable : Drawables)
	{
		if (Drawable->IsVisible())
		{
			Drawable->Draw(window);
		}
	}
}
