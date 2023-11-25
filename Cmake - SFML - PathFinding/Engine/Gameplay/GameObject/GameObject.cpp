#include "GameObject.h"
#include <Component/Renderer/Renderer.h>
#include <Component/Transform/Transform.h>

GameObject::GameObject(std::string _Name)
{
	Name = _Name;

	CTransform = new Transform(*this);
	Components.push_back(CTransform);
}

void GameObject::Start()
{
	for (IComponent *c : Components)
		c->Start();
}

void GameObject::Update(float DeltaTime)
{
	for (IComponent *c : Components)
		c->Update(DeltaTime);
}

void GameObject::Destroy()
{
	for (IComponent *c : Components)
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

void GameObject::Draw(sf::RenderWindow &window) const
{
	if (!GetComponent<Renderer>())
		return;
	GetComponent<Renderer>()->Draw(window);
}

sf::Vector2f GameObject::GetPosition() const
{
	return CTransform->GetWorldPosition();
}

void GameObject::SetPosition(const sf::Vector2f NewPosition)
{
	CTransform->SetWorldPosition(NewPosition);
}

void GameObject::AddWorldPosition(sf::Vector2f UpPosition)
{
	CTransform->AddWorldPosition(UpPosition);
}

void GameObject::OnCollisionEnter(GameObject *OtherGameObject) {}

void GameObject::OnCollisionStay(GameObject *OtherGameObject) {}

void GameObject::OnCollisionExit(GameObject *OtherGameObject) {}
