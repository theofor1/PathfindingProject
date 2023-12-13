#pragma once

#include <SFML/Graphics.hpp>

class Line
{
public:
	Line(sf::Vector2f pos1, sf::Vector2f pos2, sf::Color color = sf::Color::White);

	sf::Vertex line[2];

	void Draw(sf::RenderWindow& window) const;
};


