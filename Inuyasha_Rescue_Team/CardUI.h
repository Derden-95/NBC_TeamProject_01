#pragma once
#include "UIWidget.h"
#include "Card.h"
#include <vector>

class CardUI : public UIWidget
{
public:
	CardUI(int width, int height) :UIWidget(width, height) {
		_Count_Row = height / 6;
		_Count_Column = width / 12;
		_CanSeeCardMaxCount = _Count_Row * _Count_Column;
	}

	CardUI(int width, int height, int spawnX, int spawnY) :UIWidget(width, height, spawnX, spawnY) {
		_Count_Row = height / 6;
		_Count_Column = width / 12;
		_CanSeeCardMaxCount = _Count_Row * _Count_Column;
	}

private:
	int _Count_Row = 0;
	int _Count_Column = 0;
	int _CanSeeCardMaxCount = 0;

public:
	void PrintCards(std::vector<Card*> Cards);
	void DrawMoveCard(Card_Move& Card, int x, int y); 
	void DrawAttackCard();
	void DrawGuardCard();
	void DrawHealCard();
private:
};

