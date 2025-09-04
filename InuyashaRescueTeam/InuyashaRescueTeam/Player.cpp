#include "Player.hpp"
#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include "Card.hpp"
#include "C_Move.hpp"
#include "C_Guard.hpp"
#include "C_Attack.hpp"

void setCursorPosition(int x, int y)
{
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void hideCursor()
{
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

int getCurrentCursorLine()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
    {
        return csbi.dwCursorPosition.Y;
    }
    return -1;
}

void clearLine(int lineNumber)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    COORD startCoords = { 0, (SHORT)lineNumber };
    DWORD consoleSize = csbi.dwSize.X;
    DWORD charsWritten;
    FillConsoleOutputCharacter(hConsole, ' ', consoleSize, startCoords, &charsWritten);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, consoleSize, startCoords, &charsWritten);
    setCursorPosition(0, lineNumber);
}

Player::Player(const std::string& name, int level, int hp, int stamina, int atk, int def)
    : Entity(name, level, hp, stamina, atk, def)
{
    this->EXP = 0;
    this->maxEXP = 100 * this->Level;
    this->Money = 0;
}

Player::~Player() {
    for (Card* card : cards) {
        delete card;
    }
    cards.clear();
}

int Player::GetMoney() const { return Money; }
int Player::GetEXP() const { return EXP; }
int Player::GetMaxEXP() const { return maxEXP; }

void Player::Move(Direction dir)
{
    int nextX = GetPosX();
    int nextY = GetPosY();

    switch (dir)
    {
    case Direction::UP:    nextY--; break;
    case Direction::DOWN:  nextY++; break;
    case Direction::LEFT:  nextX--; break;
    case Direction::RIGHT: nextX++; break;
    }

    if (nextX >= 0 && nextY >= 0)
    {
        setPosX(nextX);
        setPosY(nextY);
    }
    else
    {
        std::cout << "***** 그 방향으로 이동할 수 없습니다. (좌표 음수 진입) *****" << std::endl;
    }
}

void Player::PrintPosition() const
{
    std::cout << "현재 위치: (" << GetPosX() << ", " << GetPosY() << ")" << std::endl;
}

void Player::PrintStatus() const
{
    std::cout << "***** 플레이어 상태 출력 ******" << std::endl;
    clearLine(getCurrentCursorLine());
    std::cout << "  ㄴ 이름(Name) : " << GetName() << std::endl;
    clearLine(getCurrentCursorLine());
    std::cout << "  ㄴ 레벨(LV) : " << GetLv() << std::endl;
    clearLine(getCurrentCursorLine());
    std::cout << "  ㄴ (현재 EXP: " << GetEXP() << "/" << GetMaxEXP() << ")" << std::endl;
    clearLine(getCurrentCursorLine());
    std::cout << "  ㄴ 스테미너(Stamina) : " << GetStamina() << std::endl;
    clearLine(getCurrentCursorLine());
    std::cout << "  ㄴ 공격력(ATK) : " << GetATK() << std::endl;
    clearLine(getCurrentCursorLine());
    std::cout << "  ㄴ 방어력(DEF) : " << GetDEF() << std::endl;
    clearLine(getCurrentCursorLine());
    std::cout << "  ㄴ 현재 위치: (" << GetPosX() << ", " << GetPosY() << ")" << std::endl;
    std::cout << "********************************" << std::endl;
}

void Player::AddEXP(int amount)
{
    EXP += amount;
    clearLine(getCurrentCursorLine());
    std::cout << "***** " << GetName() << "이(가) 경험치 " << amount << "을(를) 획득했습니다. (현재 EXP: " << EXP << "/" << maxEXP << ") *****" << std::endl;
    while (EXP >= maxEXP) { LevelUP(); }
}

void Player::LevelUP()
{
    EXP -= maxEXP;
    Level++;
    maxEXP = 100 * Level;
    HP += 20;
    Stamina += 10;
    ATK += 5;
    DEF += 2;
    clearLine(getCurrentCursorLine());
    std::cout << "***** 레벨업! " << GetName() << "의 레벨이 " << GetLv() << "이(가) 되었습니다! *****" << std::endl;
    clearLine(getCurrentCursorLine());
    std::cout << "***** HP, 스태미나, 공격력, 방어력이 상승했습니다. *****" << std::endl;
}

void Player::AddCard(Card* newCard)
{
    cards.push_back(newCard);
    std::cout << GetName() << "이(가) 새로운 카드 '" << newCard->C_GetName() << "'를 획득했습니다!\n";
}

void Player::ShowCards() const
{
    if (cards.empty()) {
        std::cout << "보유한 카드가 없습니다.\n";
        return;
    }
    std::cout << "========== 보유 카드 목록 ==========\n";
    for (size_t i = 0; i < cards.size(); ++i) {
        std::cout << i + 1 << ". ";
        std::cout << "이름: " << cards[i]->C_GetName();
        std::cout << ", 비용: " << cards[i]->C_GetCost();
        C_Attack* attackCard = dynamic_cast<C_Attack*>(cards[i]);
        if (attackCard) {
            std::cout << ", 공격력: " << attackCard->A_GetATK();
        }
        else {
            C_Move* moveCard = dynamic_cast<C_Move*>(cards[i]);
            if (moveCard) {
                std::cout << ", 이동 거리: " << moveCard->M_GetDistance();
            }
            else {
                C_Guard* guardCard = dynamic_cast<C_Guard*>(cards[i]);
                if (guardCard) {
                    std::cout << ", 방어력: " << guardCard->G_GetDEF();
                }
            }
        }
        std::cout << "\n";
    }
    std::cout << "====================================\n";
}

size_t Player::GetCardCount() const {
    return cards.size();
}