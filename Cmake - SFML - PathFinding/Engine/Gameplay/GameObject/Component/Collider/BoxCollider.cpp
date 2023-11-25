#include "BoxCollider.h"
#include <iostream>

BoxCollider::BoxCollider(GameObject& gameObject) : ICollider(gameObject)
{
	m_debugRectangle.setOutlineColor(sf::Color::Green);
	m_debugRectangle.setOutlineThickness(2);
	m_debugRectangle.setFillColor(sf::Color::Transparent);
}

void BoxCollider::SetColliderSize(sf::Vector2f size)
{
	m_RenderRect.width = size.x;
	m_RenderRect.height = size.y;
	m_debugRectangle.setSize(size);
}

void BoxCollider::Start()
{
	ICollider::Start();
}

void BoxCollider::Update(float DeltaTime)
{
	ICollider::Update(DeltaTime);
}

void BoxCollider::Destroy()
{
}