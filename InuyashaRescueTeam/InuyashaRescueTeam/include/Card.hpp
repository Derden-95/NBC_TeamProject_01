#pragma once
#include <string>

class Card {
protected:
    std::string Name = "tmp";
    int Cost = 0;
    int Gold = 0;
public:
    Card(std::string n, int C, int G);
    std::string C_GetName() const;
    int C_GetCost() const;
    int C_GetGold() const;
    virtual ~Card() {}
};