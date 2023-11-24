#pragma once

#include <iostream>

class Weapon
{
public:
    Weapon();
    ~Weapon();

protected:

    virtual void SetName(const std::string _Name);

private:

    std::string Name;
    
};
