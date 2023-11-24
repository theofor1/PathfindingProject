#pragma once

#include <iostream>

class Item
{
public:
    Item();
    ~Item();

protected:

    virtual void SetName(const std::string _Name);

private:

    std::string Name;
    
};
