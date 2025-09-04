#include "C_Move.hpp"
#include "Card.hpp"

// 생성자 정의
C_Move::C_Move(std::string n, int C, int G, int d, int dirx, int diry)
    : Card(n, C, G), distance(d), x(dirx), y(diry) {}

// 멤버 함수 정의
int C_Move::M_GetX() const {
    return x;
}

int C_Move::M_GetY() const {
    return y;
}

int C_Move::M_GetDistance() const {
    return distance;
}