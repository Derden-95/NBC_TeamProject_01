#pragma once
#include "C_Guard.hpp"
#include "Card.hpp"

// 생성자 정의
C_Guard::C_Guard(std::string n, int C, int G, int D)
    : Card(n, C, G), DEF(D) {}

// 멤버 함수 정의
int C_Guard::G_GetDEF() const {
    return DEF;
}