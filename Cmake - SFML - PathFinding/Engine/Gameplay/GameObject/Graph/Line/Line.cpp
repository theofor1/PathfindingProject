#include "Line.h"

Line::Line(sf::Vector2f pos1, sf::Vector2f pos2, sf::Color color)
{
	line[0] = sf::Vertex(pos1);
	line[1] = sf::Vertex(pos2);

	line[0].color = color;
	line[1].color = color;
}

void Line::Draw(sf::RenderWindow& window) const
{
	window.draw(line, 2, sf::Lines);
}