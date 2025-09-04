#include "CardUI.h"

void CardUI::PrintCards(std::vector<Card*> Cards)
{
	GoToXY(_spawnX, _spawnY);
	
	int CardCount_Showed = 0;
	Card* card;
	int drawX = 0;
	int drawY = 0;
	while (CardCount_Showed != _CanSeeCardMaxCount || Cards.size() != _CanSeeCardMaxCount)
	{
		drawX = (CardCount_Showed / _Count_Column) * 12;
		drawY = (CardCount_Showed / _Count_Row) * 6;

		card = Cards[CardCount_Showed];

		GoToXY(_spawnX + drawX, _spawnY + drawY);
		std::cout << "NAMENAMENAME";
		GoToXY(_spawnX + drawX, _spawnY + drawY + 1);
		std::cout << "NAMENAMENAME";
		GoToXY(_spawnX + drawX, _spawnY + drawY + 2);
		std::cout << "NAMENAMENAME";

		GoToXY(_spawnX + drawX, _spawnY + drawY + 3);
		std::cout << "DM : " << card->_Value;
		GoToXY(_spawnX + drawX, _spawnY + drawY + 5);
		std::cout << "EN : " << card->_Stamina_cost;

		GoToXY(_spawnX + drawX + 9, _spawnY + drawY + 3);

		//DrawMoveCard(_spawnX + drawX + 9, _spawnY + drawY + 3);
	}

	for (Card* Card : Cards)
	{
		std::cout << "Card Name" << std::endl;
		std::cout << "DM : " << Card->_Value << std::endl;
		std::cout << "EN : " << Card->_Stamina_cost << std::endl;

		switch (Card->_Type)
		{
		case Move:
			break;
		case Guard:
			break;
		case Attack:
			break;
		default:
			break;
		}
	}
}

void CardUI::DrawMoveCard(Card_Move& Card, int x, int y)
{
	GoToXY(x, y);
	std::cout << "■■■"; 
	GoToXY(x, y + 1);
	std::cout << "■■■";
	GoToXY(x, y + 2);
	std::cout << "■■■";
	
	tbColor(GREEN, BLACK);
	GoToXY(x, y + 2);
	std::cout << "■";
}

