#include "Character.h"

void Character::setHealth(int num)
{
	if (0 <= num <= 100) {
		health = num;
	}
}

Character::Character(const int Num, double(&hitBox)[2]):playerNum(Num), InGameObj(hitBox)
//initialize a character
{
	jumpSpeed = getHitBox()[1] * 2;//the jump speed is set to be double the character's height
	movementSpeed = getHitBox()[0] * 2;//the movement speed is set to be double the width
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
