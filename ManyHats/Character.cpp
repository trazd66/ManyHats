#include "Character.h"

void Character::setHealth(int num)
{
	if (0 <= num <= 100) {
		this->health = num;
	}
}

Character::Character(const int Num, double(&hitBox)[2]):playerNum(Num), InGameObj(hitBox)
//initialize a character
{
}

void Character::jump()
{
	if (InGameObj::getAirborneStatus == false) {
		InGameObj::setAirborneStatus(true);
		InGameObj::setY_vel(jumpSpeed);
	}
}

void Character::moveLeft()
{
	InGameObj::setX_vel(-movementSpeed);
}

void Character::moveRight()
{
	InGameObj::setX_vel(movementSpeed);
}


void Character::throwHat()
{
}

void Character::fetchHat()
{
}
