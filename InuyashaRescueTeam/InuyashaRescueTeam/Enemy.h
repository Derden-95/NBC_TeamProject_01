#pragma once
#include "Entity.hpp"
#include "Card.hpp"
#include <vector>

class Enemy : public Entity
{
private:
    std::string mob_name;
    int drop_money;
    int drop_exp;
    std::vector<Card*> cards; // 적의 카드 덱

public:
    Enemy(const std::string& name, int lvl, int hp, int stam, int atk, int def, int money, int exp);
    ~Enemy(); // 소멸자 추가: 할당된 카드 메모리 해제
    void Act(Entity* target);
    void AddCard(Card* newCard); // 적에게 카드를 추가하는 함수
    std::string GetMob_Name() const;
    int GetDrop_money() const;
    int GetDrop_exp() const;
};