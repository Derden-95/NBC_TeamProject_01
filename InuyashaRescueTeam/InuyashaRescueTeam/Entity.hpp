#pragma once
#include <iostream>
#include <string>

class Entity {
protected:
    std::string Name;
    int Level;
    int HP;
    int maxHP;
    int Stamina;
    int ATK;
    int DEF;
    int posX;
    int posY;

public:
    Entity(const std::string& name, int level, int hp, int stamina, int atk, int def);
    virtual ~Entity();

    void TakeDamage(int damage);
    void Heal(int amount);

    int GetLv() const;
    int GetHP() const;
    int GetStamina() const;
    int GetATK() const;
    int GetDEF() const;
    std::string GetName() const;
    int GetMaxHP() const;
    int GetPosX() const;
    int GetPosY() const;
    void setPosX(int x);
    void setPosY(int y);
};