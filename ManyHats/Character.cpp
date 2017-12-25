#include "Character.h"

int Character::getHealth()
{
	return this->health;
}

Character::Character(int playerNum): health(100)
{
	this->playerNum = playerNum;
}

void Character::jump()
{
}

void Character::move()
{
}

void Character::throwHat()
{
}
