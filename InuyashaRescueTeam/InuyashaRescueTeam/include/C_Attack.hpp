#pragma once
#include "Card.hpp"
#include <vector>

class C_Attack : public Card {
private:
    int ATK; // = 0; 부분을 제거
    bool Range[3][3];
public:
    C_Attack(std::string n, int C, int G, int A, bool r[3][3]);
    int A_GetATK() const;
    bool (*A_GetRange())[3];
    virtual ~C_Attack() {}
};