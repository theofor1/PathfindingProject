#include "Renderer.h"
#include <Engine/Render/Drawable/IDrawable.h>
#include <GameObject/GameObject.h>
#include <Component/Transform/Transform.h>

Renderer::Renderer(GameObject& gameObject) : IComponent(gameObject)
{}

void Renderer::Start()
{
}

void Renderer::Update(float FDeltaTime)
{
	for (auto & Drawable : Drawables)
	{
		// Set Drawable transform with parent transform
		Drawable->SetWorldTransform(GetGameObject().GetComponent<Transform>()->GetTransform());
		Drawable->Update(FDeltaTime);
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
