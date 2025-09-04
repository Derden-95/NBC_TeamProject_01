#include "BattleManager.h"
#include <windows.h>
#include <iostream>

enum Color {
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	MAGENTA = 5,
	BROWN = 6,
	LIGHTGRAY = 7,
	DARKGRAY = 8,
	LIGHTBLUE = 9,
	LIGHTGREEN = 10,
	IGHTCYAN = 11,
	LIGHTRED = 12,
	LIGHTMAGENTA = 13,
	YELLOW = 14,
	WHITE = 15
};

using namespace std;

void BattleManager::tbColor(unsigned short textColor = 7, unsigned short backColor = 0) {
	int color = textColor + backColor * 16;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void BattleManager::PrintPlayerCardList(int posx, int posy)
{
	GoToXY(posx, posy);

	CONSOLE_SCREEN_BUFFER_INFO wherecurser;	
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &wherecurser);


	while (true)
	{
		int index = 1;
		for (Card* card : _p1._Cards)
		{
			GoToXY(posx, posy);
			cout << "\r" << string(50, ' ') << std::flush << endl;
			cout << "\r" << string(50, ' ') << std::flush << endl;
			cout << "\r" << string(50, ' ') << std::flush << endl;
			cout << "\r" << string(50, ' ') << std::flush << endl;
			cout << "\r" << string(50, ' ') << std::flush << endl;
			GoToXY(posx, posy);
			cout << index << "번째 카드" << endl;
			index++;

			switch (card->_Type)
			{
			case CardType::Move:
			{
				Card_Move* card_move = static_cast<Card_Move*>(card);
				cout << "카드 타입 : 이동, 위로 : " << card_move->_Up << "칸 오른쪽 : " << card_move->_Right << "칸 으로이동" << endl;
				for (size_t i = 0; i < 3; i++)
				{
					if (i == 1) {
						cout << "□■□" << endl;
						continue;
					}
					else {
						cout << "□□□" << endl;
					}
				}
				GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &wherecurser);
				GoToXY(wherecurser.dwCursorPosition.X + 1, wherecurser.dwCursorPosition.Y - 2);
				cout << "■";
				GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &wherecurser);
				GoToXY(wherecurser.dwCursorPosition.X - 1 + card_move->_Right, wherecurser.dwCursorPosition.Y - card_move->_Up);
				tbColor(GREEN, BLACK);
				cout << "■";
				break;
			}
			case CardType::Attack:
			{
				Card_Attack* card_attack = static_cast<Card_Attack*>(card);
				cout << "카드 타입 : 공격, 데미지량 : " << card->_Value << ", ST 소모량 : " << card->_Stamina_cost << endl;

				bool (*range)[3] = card_attack->_Range;
				
				for (size_t i = 0; i < 3; i++)
				{
					for (size_t k = 0; k < 3; k++)
					{
						if (range[i][k] == true)
						{
							tbColor(GREEN, BLACK);
							cout << "■";
						}
						else {
							tbColor();
							cout << "□";
						}
					}
					cout << endl;
				}

				GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &wherecurser);
				GoToXY(wherecurser.dwCursorPosition.X + (card_attack->_PosX - 1), wherecurser.dwCursorPosition.Y - 3 + (card_attack->_PosY - 1));
				tbColor();
				cout << "■";
				break;
			}
			case CardType::Guard:
				cout << "카드 타입 : 방어, 방어량 : " << card->_Value << ", ST 소모량 : " << card->_Stamina_cost << endl;
				break;
			case CardType::HP_Healing:
				cout << "카드 타입 : HP 회복, 회복량 : " << card->_Value << ", ST 소모량 : " << card->_Stamina_cost << endl;
				break;
			case CardType::Stamina_Healing:
				cout << "카드 타입 : ST 회복, 회복량 : " << card->_Value << ", ST 소모량 : " << card->_Stamina_cost << endl;
				break;
			default:
				break;
			}
			tbColor();
			cin.get();
		}
	}
}

void BattleManager::PrintStatus()
{
	tbColor(0, YELLOW);
	cout << " ■■■■■■■■■■ ▥HP▥ ■■■■■■■■■■ " << endl;
	cout << " ■■■■■■■■■■ ▥ST▥ ■■■■■■■■■■ " << endl;
	tbColor();


	//print p1
	GoToXY(1, 0);
	tbColor(RED, YELLOW);
	for (size_t i = 0; i < _p1._HP / 10; i++)
	{
		cout << "■";
	}
	GoToXY(1, 1);
	tbColor(BROWN, YELLOW);
	for (size_t i = 0; i < _p1._Stamina / 10; i++)
	{
		cout << "■";
	}

	//print p2
	GoToXY(17, 0);
	tbColor(RED, YELLOW);
	for (size_t i = 0; i < _p2._HP / 10; i++)
	{
		cout << "■";
	}
	GoToXY(17, 1);
	tbColor(BROWN, YELLOW);
	for (size_t i = 0; i < _p2._Stamina / 10; i++)
	{
		cout << "■";
	}

	tbColor();
}

void BattleManager::PrintGrid(int posx, int posy)
{
	int x = posx;
	int y = posy;
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			GoToXY(7 * j + x, 3 * i + y);
			cout << "┌─────┐" << endl;
			GoToXY(7 * j + x, 3 * i + 1 + y);
			cout << "│     │" << endl;
			GoToXY(7 * j + x, 3 * i + 2 + y);
			cout << "└─────┘" << endl;
		}
	}

	PrintPlayers(x, y);
}

void BattleManager::GoToXY(int x, int y)
{
	COORD pos = { x,y }; //x, y 좌표 설정
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); //커서 설정
}

void BattleManager::PrintPlayers(int posx, int posy)
{
	GoToXY(7 * (p1x + 1) - 4 + posx, (3 * p1y) + 1 + posy);
	tbColor(GREEN,BLACK);
	cout << "@";

	GoToXY(7 * (p2x + 1) - 4 + posx, (3 * p2y) + 1 + posy);
	tbColor(RED, BLACK);
	cout << "#";
	tbColor();
	//GoToXY(0,20);
}
