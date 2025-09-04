#pragma once
enum CardType
{
	None,
	Move,
	Attack,
	HP_Healing,
	Stamina_Healing,
	Guard
};

class Card
{
public:
	Card(float value, float stamina_cost) {
		_Value = value;
		_Stamina_cost = stamina_cost;
	}

	CardType _Type = None;

	float _Value;

	float _Stamina_cost;
private:
};

class Card_Move : public Card
{
public:
	Card_Move(float value, float stamina_cost, int up, int right) : Card(value, stamina_cost) {
		_Type = Move;
		_Up = up;
		_Right = right;
	}

	int _Up;
	int _Right;

private:
};

class Card_Attack : public Card
{
public:
	Card_Attack(float value, float stamina_cost, bool (&range)[3][3], int posX, int posY) : Card(value, stamina_cost){
		_Type = Attack;
		_Range = range;
		_PosX = posX;
		_PosY = posY;
	}

	int _PosX;

	int _PosY;

	bool (*_Range)[3];
	//bool Range[3][3];

private:	

};

class Card_HP_Healing : public Card {
public:
	Card_HP_Healing(float value, float stamina_cost) : Card(value, stamina_cost) {
		_Type = HP_Healing;
		_Value = value;
		_Stamina_cost = stamina_cost;
	}
};

class Card_Stamina_Healing : public Card {
public:
	Card_Stamina_Healing(float value, float stamina_cost) : Card(value, stamina_cost) {
		_Type = Stamina_Healing;
		_Value = value;
		_Stamina_cost = stamina_cost;
	}
};

class Card_Guard : public Card {
public:
	Card_Guard(float value, float stamina_cost) : Card(value, stamina_cost) {
		_Type = Guard;


		_Value = value;
		_Stamina_cost = stamina_cost;
	}
};
