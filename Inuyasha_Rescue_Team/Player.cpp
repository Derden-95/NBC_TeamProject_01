#include "Player.h"

void Player::AddCard(Card& card)
{
	_Cards.push_back(&card);
}
