#include "Character.h"

void Character::setHealth(int num)
{
	this->health = num;
}

Character::Character(const int Num, double(&arr)[2]):playerNum(Num), InGameObj(arr)
{

}

void Character::jump()
{
}

void Character::moveLeft()
{
}

void Character::moveRight()
{
}


void Character::throwHat()
{
}
