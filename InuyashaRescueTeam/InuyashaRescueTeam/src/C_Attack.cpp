#include "C_Attack.hpp"
#include "Card.hpp"
#include <cstring> // memcpy 사용

// 생성자 정의
C_Attack::C_Attack(std::string n, int C, int G, int A, bool r[3][3])
    : Card(n, C, G), ATK(A) {
    // 2차원 배열 복사
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            Range[i][j] = r[i][j];
        }
    }
}

// 멤버 함수 정의
int C_Attack::A_GetATK() const {
    return ATK;
}

bool (*C_Attack::A_GetRange())[3] {
    return Range;
}