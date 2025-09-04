#pragma once
#include <vector>
#include "Card.h"

using namespace std;

class Player
{
public:
	float _HP = 70;
	const float _Max_HP = 100;

	float _Stamina = 50;
	const float _Max_stamina = 100; 

	vector<Card*> _Cards;

	void AddCard(Card& card);

private:
	
};

