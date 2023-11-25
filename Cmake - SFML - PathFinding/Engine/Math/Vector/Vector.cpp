#include "Vector.h"
#include <cmath>

#define PI 3.14159265358979323846 /* pi */

void Vector::Normalized(sf::Vector2f &Vec)
{
	if (Vec.y != 0 || Vec.x != 0)
	{
		float norme = std::sqrt(Vec.x * Vec.x + Vec.y * Vec.y);
		Vec = Vec / norme;
	}
}

sf::Vector2f Vector::GetDirection(sf::Vector2f VecStart, sf::Vector2f VecEnd)
{
	sf::Vector2f Direction = (VecEnd - VecStart);
	Normalized(Direction);
	return Direction;
}

float Vector::GetDistance(sf::Vector2f Vec1, sf::Vector2f Vec2)
{
	return sqrt(pow(Vec1.x - Vec2.x, 2) + pow(Vec1.y - Vec2.y, 2));
}

float Vector::DotProduct(sf::Vector2f Vec1, sf::Vector2f Vec2)
{
	float normeV1 = sqrt(pow(Vec1.x, 2) + pow(Vec1.y, 2));
	float normeV2 = sqrt(pow(Vec2.x, 2) + pow(Vec2.y, 2));

	float ps = Vec1.x * Vec2.x + Vec1.y * Vec2.y;

	float deg;
	deg = ps / (normeV1 * normeV2);
	deg = acos(deg) * 180 / PI;

	return deg;
}

bool Vector::IsColineaire(sf::Vector2f Vec1, sf::Vector2f Vec2)
{
	float val = Vec1.x * Vec2.y - Vec2.x * Vec1.y;
	if (val == 0)
		return true;
	return false;
}

bool Vector::IsColineaire(sf::Vector3f Vec1, sf::Vector3f Vec2)
{
	if (HasMemberNull(Vec1) || HasMemberNull(Vec2))
		return false;

	return false;
}

bool Vector::AreColineaire(sf::Vector2f Vec1, sf::Vector2f Vec2, sf::Vector2f Vec3)
{
	if (!IsColineaire(Vec1, Vec2))
		return false;
	else if (!IsColineaire(Vec1, Vec3))
		return false;

	return true;
}

bool Vector::GetCartesienne(sf::Vector2f Vec1, sf::Vector2f Vec2)
{

	return true;
}

bool Vector::HasMemberNull(sf::Vector3f Vec)
{
	if (Vec.x == 0 || Vec.y == 0 || Vec.z == 0)
		return true;
	return false;
}
