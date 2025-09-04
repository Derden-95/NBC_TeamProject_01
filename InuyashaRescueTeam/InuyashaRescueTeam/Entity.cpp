#include "Entity.hpp"

Entity::Entity(const std::string& name, int level, int hp, int stamina, int atk, int def)
    : Name(name), Level(level), HP(hp), maxHP(hp), Stamina(stamina), ATK(atk), DEF(def), posX(0), posY(0) {
}

Entity::~Entity() {}

void Entity::TakeDamage(int damage)
{
    int finalDamage = damage - DEF;
    if (finalDamage < 0) { finalDamage = 0; }
    HP -= finalDamage;
    if (HP < 0) { HP = 0; }
    std::cout << Name << "이(가) " << finalDamage << "의 데미지를 입었습니다. 현재 HP: " << HP << std::endl;
}

void Entity::Heal(int amount) {
    HP += amount;
    if (HP > maxHP) {
        HP = maxHP;
    }
    std::cout << Name << "이(가) " << amount << "의 HP를 회복했습니다. 현재 HP: " << HP << std::endl;
}

int Entity::GetLv() const { return Level; }
int Entity::GetHP() const { return HP; }
int Entity::GetStamina() const { return Stamina; }
int Entity::GetATK() const { return ATK; }
int Entity::GetDEF() const { return DEF; }
std::string Entity::GetName() const { return Name; }
int Entity::GetMaxHP() const { return maxHP; }
int Entity::GetPosX() const { return posX; }
int Entity::GetPosY() const { return posY; }
void Entity::setPosX(int x) { this->posX = x; }
void Entity::setPosY(int y) { this->posY = y; }