#pragma once
#include "Card.hpp"

class C_Move : public Card {
private:
    int distance = 1;
    int x = 0;
    int y = 0;
public:
    C_Move(std::string n, int C, int G, int d, int dirx, int diry);
    int M_GetX() const;
    int M_GetY() const;
    int M_GetDistance() const;
    virtual ~C_Move() {}
};