#include "Card.hpp"

// 생성자 정의
Card::Card(std::string n, int C, int G) : Name(n), Cost(C), Gold(G) {}

// 멤버 함수 정의
std::string Card::C_GetName() const {
    return Name;
}

int Card::C_GetCost() const {
    return Cost;
}

int Card::C_GetGold() const {
    return Gold;
}