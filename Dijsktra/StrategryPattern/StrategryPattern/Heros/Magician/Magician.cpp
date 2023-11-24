#include "Magician.h"
#include "Heros/TypeHero.h"
#include <iostream>

Magician::Magician() : Heros() {
    
}

Magician::~Magician() {
    Heros::~Heros();
}

void Magician::Combat() {
    m_WayToFight = std::make_unique<FigthWithStick>();
}

void Magician::Heal() {
    std::cout << "Je heal.\n";
}