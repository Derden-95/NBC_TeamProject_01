#pragma once
#include "Player.h"

class BattleManager
{
public:
	BattleManager(Player& p1, Player& p2) : _p1(p1), _p2(p2){
		
	};

private:
	Player& _p1;
	Player& _p2;

	int p1x = 0;
	int p1y = 1;

	int p2x = 3;
	int p2y = 1;

	int _Grid[3][4] = { {0, 0, 0, 0}, {1, 0, 0, 1}, {0, 0, 0, 0} };

public:
	void BattleStart();

//private:
	void EnemyChooseCard();
	void PrioritySortCards();
	void TurnStart();
	void PlayerChooseCard();

	void PrintPlayerCardList(int posx, int posy);

	void tbColor(unsigned short textColor, unsigned short backColor);

	void PrintStatus();

	void PrintGrid(int posx, int posy);
	void GoToXY(int x, int y);

	void PrintPlayers(int posx, int posy);
};

