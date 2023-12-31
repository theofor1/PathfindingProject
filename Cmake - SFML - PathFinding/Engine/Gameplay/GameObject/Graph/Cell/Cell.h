#ifndef CELL_H
#define CELL_H

#pragma once

#include <GameObject/GameObject.h>
#include <SFML/Graphics/RectangleShape.hpp>

enum class CellType
{
	NORMAL,
	BLOCK,
	TELEPORTATION
};


class Cell : public GameObject
{
public:
	Cell(std::string Name = "", sf::Vector2f Position = sf::Vector2f(0, 0), int _SideSize = 100, const CellType _CellType = CellType::NORMAL);
	// Cell(std::string Name = "", sf::Vector2f Position = sf::Vector2f(0, 0), int _SideSize = 100, const bool _IsAlive = true);
	~Cell();

	virtual void Start() override;
	virtual void Update(float DeltaTime) override;
	virtual void Destroy() override;

	virtual void Draw(sf::RenderWindow &window) const;

	virtual sf::RectangleShape GetRectangleShape() const;
	sf::FloatRect GetRect() const;

	virtual void SetIsAlive(const bool _IsAlive);
	virtual bool GetIsAlive() const;

	virtual void SetCellType(const CellType NewCellType);
	virtual CellType GetCellType() const;
	virtual void SetOtherCellTypeTeleportation(Cell* _OtherCellTypeTeleportation);
	virtual void UnsetOtherCellTypeTeleportation();

	virtual void SetSize(const int _SideSize);
	virtual void SetPosition(const sf::Vector2f Position);
	
	Cell *OtherCellTypeTeleportation;

private:
	CellType CurrentCellType;
	bool IsAlive;

	sf::RectangleShape Rectangle;
	sf::FloatRect Rect;

	int SideSize;
	sf::Vector2f Size;

	sf::Color ColorOnAlive = sf::Color::Blue;
	sf::Color ColorOnDead = sf::Color::Black;

	void UpdateColor();
};

#endif