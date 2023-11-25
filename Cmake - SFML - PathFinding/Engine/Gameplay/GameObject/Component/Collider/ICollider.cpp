#include "ICollider.h"
#include <GameObject/GameObject.h>
#include <Component/Transform/Transform.h>

ICollider::ICollider(GameObject& gameObject) : IComponent(gameObject)
{
}

void ICollider::SetColliderSize(sf::Vector2f size)
{
	m_RenderRect.width = size.x;
	m_RenderRect.height = size.y;
	m_debugRectangle.setSize(size);
}

void ICollider::SetColliderPositionLocal(sf::Vector2f pos)
{
	LocalPosition = pos;
}

bool ICollider::IsOnCollisionWidth(sf::FloatRect OtherRect)
{

	return GetRect().intersects(OtherRect);
}

void ICollider::CancelCollisionWith(ICollider *OtherCollider)
{
	sf::FloatRect intersect;
	GetRect().intersects(OtherCollider->GetRect(), intersect);

	sf::Vector2f cancelVector = GetVectorMoveToCancelCollision(OtherCollider->GetRect());
	cancelVector.x *= intersect.width + 1;
	cancelVector.y *= intersect.height + 1;

	GetGameObject().GetComponent<Transform>()->AddWorldPosition(cancelVector);
}

void ICollider::SetLayer(Layers layers)
{
	mask = layers;
}

void ICollider::AddLayer(Layers layers)
{
	mask += layers;
}

void ICollider::RemoveLayer(Layers layers)
{
	mask = ~mask & layers;
}

bool ICollider::HasLayer(Layers layers)
{
	return (mask & layers);
}

char ICollider::GetMask() const
{
	return mask;
}

void ICollider::SetWasOnCollision(bool _isOnCollision)
{
	_WasOnCollision = _isOnCollision;
}

bool ICollider::WasOnCollision()
{
	return _WasOnCollision;
}

sf::FloatRect ICollider::GetRect() const
{
	return m_RenderRect;
}


void ICollider::Start()
{
}

void ICollider::Update(float DeltaTime)
{
	UpdateRectPosition();
}

void ICollider::Destroy()
{
}

std::string ICollider::GetComponentName() const
{
	return std::string();
}

void ICollider::UpdateRectPosition()
{
	sf::Vector2f newPos = GetGameObject().GetComponent<Transform>()->GetWorldPosition() + LocalPosition;

	m_RenderRect.left = newPos.x;
	m_RenderRect.top = newPos.y;

	m_debugRectangle.setPosition(newPos);
}


// Private 

sf::Vector2f ICollider::GetVectorMoveToCancelCollision(sf::FloatRect OtherRect)
{
	// Get depth distance

	// Left
	float depthDistanceLeft = fabs(m_RenderRect.left + (m_RenderRect.width - OtherRect.left));

	// Right
	float depthDistanceRight = fabs(m_RenderRect.left - (OtherRect.left + OtherRect.width));

	// Up
	float depthDistanceUp = fabs((m_RenderRect.top + m_RenderRect.height) - OtherRect.top);

	// Down
	float depthDistanceDown = fabs(m_RenderRect.top - (OtherRect.top + OtherRect.height));

	// Search the less
	float minDepthDistance = depthDistanceUp;
	sf::Vector2f normalVector = sf::Vector2f(0, -1);

	if (minDepthDistance >= depthDistanceDown)
	{
		minDepthDistance = depthDistanceDown;
		normalVector = sf::Vector2f(0, 1);
	}

	if (minDepthDistance >= depthDistanceLeft)
	{
		minDepthDistance = depthDistanceLeft;
		normalVector = sf::Vector2f(-1, 0);
	}

	if (minDepthDistance >= depthDistanceRight)
	{
		minDepthDistance = depthDistanceRight;
		normalVector = sf::Vector2f(1, 0);
	}

	return normalVector;
}
