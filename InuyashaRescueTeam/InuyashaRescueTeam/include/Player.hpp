#pragma once
#include "Entity.hpp"
#include <vector>
#include <conio.h>
#include <windows.h>
#include "Card.hpp"

class Card;

void setCursorPosition(int x, int y);
void hideCursor();
int getCurrentCursorLine();
void clearLine(int lineNumber);

enum class Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Player : public Entity {
private:
    int Money;
    int EXP;
    int maxEXP;
    std::vector<Card*> cards;
    void LevelUP();

public:
    Player(const std::string& name, int level, int hp, int stamina, int atk, int def);
    ~Player();

    int GetMoney() const;
    int GetEXP() const;
    int GetMaxEXP() const;

    void Move(Direction dir);
    void PrintPosition() const;
    void PrintStatus() const;
    void AddCard(Card* newCard);
    void AddEXP(int amount);
    void ShowCards() const;
    size_t GetCardCount() const;
};