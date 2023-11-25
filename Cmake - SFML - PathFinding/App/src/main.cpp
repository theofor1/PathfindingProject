#include <SFML/Graphics.hpp>
#include <iostream>

#include "Toto.h"
// #include "AnotherToto.h"
#include "AnotherToto/AnotherToto.h"
#include <AnotherToto/AnotherToto.h>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);

    Toto test;
    AnotherToto anotherTest;

    std::cout << test.a << "\n";
    std::cout << anotherTest.a << "\n";

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}