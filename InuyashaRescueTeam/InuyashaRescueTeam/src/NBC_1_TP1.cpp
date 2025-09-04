#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <cmath>

#include "Entity.hpp"
#include "Player.hpp"
#include "Enemy.h"
#include "Card.hpp"
#include "C_Move.hpp"
#include "C_Guard.hpp"
#include "C_Attack.hpp"

// Utility functions (assuming these are defined in Player.cpp)
void setCursorPosition(int x, int y);
void hideCursor();
int getCurrentCursorLine();
void clearLine(int lineNumber);

class BattleGrid {
private:
    const int GRID_WIDTH = 4;
    const int GRID_HEIGHT = 3;
    std::vector<std::vector<Entity*>> grid;

public:
    BattleGrid() {
        grid.resize(GRID_HEIGHT, std::vector<Entity*>(GRID_WIDTH, nullptr));
    }
    ~BattleGrid() {}
    void PlaceEntity(Entity* entity, int x, int y) {
        if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT) {
            grid[y][x] = entity;
        }
    }
    void RemoveEntity(int x, int y) {
        if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT) {
            grid[y][x] = nullptr;
        }
    }
    void MoveEntity(Entity* entity, int oldX, int oldY, int newX, int newY) {
        if (newX >= 0 && newX < GRID_WIDTH && newY >= 0 && newY < GRID_HEIGHT) {
            RemoveEntity(oldX, oldY);
            PlaceEntity(entity, newX, newY);
        }
    }
    void PrintGrid() const {
        std::cout << "--- 전투 그리드 ---\n";
        for (int y = 0; y < GRID_HEIGHT; ++y) {
            for (int x = 0; x < GRID_WIDTH; ++x) {
                if (grid[y][x] == nullptr) {
                    std::cout << "[ ] ";
                }
                else if (dynamic_cast<Player*>(grid[y][x])) {
                    std::cout << "[P] ";
                }
                else {
                    std::cout << "[E] ";
                }
            }
            std::cout << "\n";
        }
        std::cout << "-------------------\n";
    }
    Entity* GetEntityAt(int x, int y) const {
        if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT) {
            return grid[y][x];
        }
        return nullptr;
    }
};

class BattleManager {
private:
    Player* player;
    Enemy* enemy;
    BattleGrid* grid;

    size_t GetPlayerCardCount_temp() { return 3; }
    Card* GetPlayerCard_temp(int index) {
        if (index == 0) return new C_Move("이동 카드", 1, 5, 2, 0, 1);
        if (index == 1) {
            bool attackRange[3][3] = { {false, true, false}, {true, true, true}, {false, true, false} };
            return new C_Attack("칼날바람", 3, 15, 30, attackRange);
        }
        if (index == 2) return new C_Guard("방어 카드", 2, 10, 20);
        return nullptr;
    }

public:
    BattleManager(Player* p, Enemy* e, BattleGrid* g) : player(p), enemy(e), grid(g) {}

    void StartCombat() {
        std::cout << "전투 시작!\n";
        grid->PlaceEntity(player, player->GetPosX(), player->GetPosY());
        grid->PlaceEntity(enemy, enemy->GetPosX(), enemy->GetPosY());
        grid->PrintGrid();

        while (!IsCombatOver()) {
            PlayerTurn();
            if (IsCombatOver()) break;
            EnemyTurn();
        }
        std::cout << "\n전투 종료!\n";
    }

    void PlayerTurn() {
        std::cout << "\n--- 플레이어의 턴 ---\n";
        player->PrintStatus();
        player->ShowCards();
        std::cout << "사용할 카드를 선택하세요 (1~" << GetPlayerCardCount_temp() << "): ";
        HandlePlayerInput();
    }

    void EnemyTurn() {
        std::cout << "\n--- 적의 턴 ---\n";
        int oldX = enemy->GetPosX();
        int oldY = enemy->GetPosY();
        enemy->Act(player);
        grid->MoveEntity(enemy, oldX, oldY, enemy->GetPosX(), enemy->GetPosY());
        grid->PrintGrid();
    }

    void HandlePlayerInput() {
        char input = _getch();
        if (input >= '1' && input <= '3') {
            int cardIndex = input - '1';

            if (cardIndex >= GetPlayerCardCount_temp()) {
                std::cout << "유효하지 않은 카드 번호입니다.\n";
                return;
            }

            Card* selectedCard = GetPlayerCard_temp(cardIndex);

            if (!selectedCard) {
                std::cout << "유효하지 않은 카드 번호입니다.\n";
                return;
            }

            C_Move* moveCard = dynamic_cast<C_Move*>(selectedCard);
            if (moveCard) {
                std::cout << moveCard->C_GetName() << " 카드를 사용했습니다. 이동할 방향을 선택하세요 (w, a, s, d): ";
                char moveInput = _getch();
                Direction dir;
                switch (moveInput) {
                case 'w': dir = Direction::UP; break;
                case 's': dir = Direction::DOWN; break;
                case 'a': dir = Direction::LEFT; break;
                case 'd': dir = Direction::RIGHT; break;
                default:
                    std::cout << "잘못된 방향입니다. 턴을 소모합니다.\n";
                    delete selectedCard;
                    return;
                }

                int oldX = player->GetPosX();
                int oldY = player->GetPosY();
                player->Move(dir);
                grid->MoveEntity(player, oldX, oldY, player->GetPosX(), player->GetPosY());
                std::cout << "플레이어가 (" << player->GetPosX() << ", " << player->GetPosY() << ")로 이동했습니다.\n";
            }

            C_Attack* attackCard = dynamic_cast<C_Attack*>(selectedCard);
            if (attackCard) {
                std::cout << attackCard->C_GetName() << " 카드를 사용했습니다!\n";
                int playerX = player->GetPosX();
                int playerY = player->GetPosY();
                int enemyX = enemy->GetPosX();
                int enemyY = enemy->GetPosY();

                int dist_x = std::abs(playerX - enemyX);
                int dist_y = std::abs(playerY - enemyY);

                if (dist_x <= 1 && dist_y <= 1 && (dist_x > 0 || dist_y > 0)) {
                    enemy->TakeDamage(attackCard->A_GetATK());
                }
                else {
                    std::cout << "공격 범위 내에 적이 없습니다.\n";
                }
            }

            C_Guard* guardCard = dynamic_cast<C_Guard*>(selectedCard);
            if (guardCard) {
                std::cout << guardCard->C_GetName() << " 카드를 사용했습니다. 방어력이 증가합니다.\n";
                player->Heal(guardCard->G_GetDEF());
            }

            delete selectedCard;
        }
        else {
            std::cout << "잘못된 입력입니다. 1, 2, 3 중 하나를 선택하세요.\n";
        }
        grid->PrintGrid();
    }

    bool IsCombatOver() const {
        return player->GetHP() <= 0 || enemy->GetHP() <= 0;
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0)));

    Player player("이누야샤", 1, 100, 50, 20, 10);
    Enemy enemy("검은 요괴", 1, 80, 40, 15, 5, 50, 30);

    BattleGrid grid;

    player.setPosX(0);
    player.setPosY(1);
    enemy.setPosX(3);
    enemy.setPosY(1);

    player.AddCard(new C_Move("이동 카드", 1, 5, 2, 0, 1));
    bool attackRange[3][3] = { {false, true, false}, {true, true, true}, {false, true, false} };
    player.AddCard(new C_Attack("칼날바람", 3, 15, 30, attackRange));
    player.AddCard(new C_Guard("방어 카드", 2, 10, 20));

    enemy.AddCard(new C_Move("이동 카드", 1, 5, 2, 0, 1));
    enemy.AddCard(new C_Attack("칼날바람", 3, 15, 30, attackRange));
    enemy.AddCard(new C_Guard("방어 카드", 2, 10, 20));

    BattleManager battleManager(&player, &enemy, &grid);
    battleManager.StartCombat();

    return 0;
}