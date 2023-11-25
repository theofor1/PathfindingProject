#include "GameObject.h"
#include <Component/Renderer/Renderer.h>
#include <Component/Transform/Transform.h>

GameObject::GameObject(std::string _Name)
{
	Name = _Name;
	Components.push_back(new Transform(*this));
}

void GameObject::Start()
{
	for (IComponent* c : Components)
		c->Start();
}

void GameObject::Update(float fDeltaTime)
{
	for (IComponent* c : Components)
		c->Update(fDeltaTime);
}

void GameObject::Destroy()
{
	for (IComponent* c : Components)
		c->Destroy();
}

void GameObject::SetName(std::string _Name)
{
	Name = _Name;
}

std::string GameObject::GetName()
{
	return Name;
}

void GameObject::Draw(sf::RenderWindow& window) const
{
	if (!GetComponent<Renderer>())
		return;
	GetComponent<Renderer>()->Draw(window);
}


void GameObject::OnCollisionEnter(GameObject* OtherGameObject) {}

void GameObject::OnCollisionStay(GameObject* OtherGameObject) {}

void GameObject::OnCollisionExit(GameObject* OtherGameObject) {}



