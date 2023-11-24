#include "Heros/Heros.h"

#pragma once

class Thief : public Heros
{
public:
    Thief();
    ~Thief();

    virtual void Combat() override;
    virtual void Heal() override;
};
