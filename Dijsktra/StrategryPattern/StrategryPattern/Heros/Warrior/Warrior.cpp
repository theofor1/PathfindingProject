#include "Warrior.h"
#include "Heros/TypeHero.h"
#include <iostream>

// Warrior::Warrior() : Heros(E_TypeHero::WARRIOR), m_WayToFight(std::make_unique<FigthWithSword>()) {
Warrior::Warrior() : Heros(std::make_unique<FigthWithSword>()) {
    // m_WayToFight = std::make_unique<FigthWithSword>();
}

Warrior::~Warrior() {
    Heros::~Heros();
}

void Warrior::Combat() {
   // m_WayToFight->Combat();
}

void Warrior::Heal() {
    std::cout << "Je ne heal pas.\n";
}