#pragma once
#include "Card.hpp"

class C_Guard : public Card {
private:
    int DEF = 0;
public:
    C_Guard(std::string n, int C, int G, int D);
    int G_GetDEF() const;
    virtual ~C_Guard() {}
};