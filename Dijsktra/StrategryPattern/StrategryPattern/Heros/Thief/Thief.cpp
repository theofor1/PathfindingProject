#include "Thief.h"
#include "Heros/TypeHero.h"
#include <iostream>

Thief::Thief() : Heros()
{
}

Thief::~Thief()
{
    Heros::~Heros();
}

void Thief::Combat()
{
    std::cout << "Je vole\n";
}

void Thief::Heal()
{
    std::cout << "Je ne heal pas.\n";
}