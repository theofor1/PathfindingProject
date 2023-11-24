#include "Heros/Heros.h"

#pragma once
class Warrior : public Heros
{
public:
    Warrior();
    ~Warrior();

    void Combat() override;
    void Heal() override;
};
