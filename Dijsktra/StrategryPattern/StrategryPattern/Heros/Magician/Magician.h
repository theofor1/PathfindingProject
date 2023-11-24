#include "Heros/Heros.h"

#pragma once

class Magician : public Heros
{
public:
    Magician();
    ~Magician();

    virtual void Combat() override;
    virtual void Heal() override;
};
