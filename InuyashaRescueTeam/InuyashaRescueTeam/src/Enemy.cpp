#include "Enemy.h"
#include "C_Move.hpp"
#include "C_Guard.hpp"
#include "C_Attack.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

// Enemy 클래스의 생성자 정의
Enemy::Enemy(const std::string& name, int lvl, int hp, int stam, int atk, int def, int money, int exp)
    : Entity(name, lvl, hp, stam, atk, def), mob_name(name), drop_money(money), drop_exp(exp) {
}

void Enemy::AddCard(Card* newCard) {
    cards.push_back(newCard);
}

Enemy::~Enemy() {
    for (Card* card : cards) {
        delete card;
    }
    cards.clear();
}

void Enemy::Act(Entity* target)
{
    if (GetHP() <= 0)
        return;

    if (cards.empty()) {
        std::cout << GetName() << "은(는) 사용할 카드가 없습니다.\n";
        return;
    }

    // 카드 덱에서 무작위로 카드 한 장 선택
    int cardIndex = std::rand() % cards.size();
    Card* selectedCard = cards[cardIndex];

    // 선택된 카드의 종류에 따라 행동 수행
    C_Move* moveCard = dynamic_cast<C_Move*>(selectedCard);
    if (moveCard) {
        std::cout << GetName() << "이(가) '" << moveCard->C_GetName() << "' 카드를 사용합니다!\n";

        int newX = GetPosX();
        int newY = GetPosY();

        // 플레이어에게 가장 가까운 방향으로 이동
        if (newX < target->GetPosX()) newX++;
        else if (newX > target->GetPosX()) newX--;

        if (newY < target->GetPosY()) newY++;
        else if (newY > target->GetPosY()) newY--;

        setPosX(newX);
        setPosY(newY);
        return;
    }

    C_Attack* attackCard = dynamic_cast<C_Attack*>(selectedCard);
    if (attackCard) {
        std::cout << GetName() << "이(가) '" << attackCard->C_GetName() << "' 카드를 사용합니다!\n";
        int deltaX = std::abs(GetPosX() - target->GetPosX());
        int deltaY = std::abs(GetPosY() - target->GetPosY());

        if (deltaX <= 1 && deltaY <= 1 && (deltaX > 0 || deltaY > 0)) {
            target->TakeDamage(attackCard->A_GetATK());
        }
        else {
            std::cout << "하지만 " << target->GetName() << "이(가) 공격 범위 밖에 있습니다.\n";
        }
        return;
    }

    C_Guard* guardCard = dynamic_cast<C_Guard*>(selectedCard);
    if (guardCard) {
        std::cout << GetName() << "이(가) '" << guardCard->C_GetName() << "' 카드를 사용합니다! 방어 태세를 취합니다.\n";
        // 임시로 방어력만큼 체력 회복으로 구현
        Heal(guardCard->G_GetDEF());
        return;
    }
    std::cout << GetName() << "은(는) 알 수 없는 카드를 사용했습니다.\n";
}