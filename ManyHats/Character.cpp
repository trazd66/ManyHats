#include "Character.h"
void Character::setHealth(int num)
{
	if (0 <= num && num <= 100) {
		health = num;
	}
}

Character::Character(const int Num, double(&hitBox)[2]):playerNum(Num), InGameObj(hitBox)
//initialize a character
{
	jumpSpeed = (int)getHitBox()[1] * 2;//the jump speed is set to be double the character's height
	movementSpeed = (int)getHitBox()[0] * 2;//the movement speed is set to be double the width
}

void Character::jump()
{
	if (InGameObj::getAirborneStatus() == false) {
		InGameObj::setAirborneStatus(true);
		InGameObj::setY_vel(jumpSpeed);
	}
}

void Character::moveLeft()
{
	faceRight = false;
	InGameObj::setX_vel(-movementSpeed);
}

void Character::moveRight()
{
	faceRight = true;
	InGameObj::setX_vel(movementSpeed);
}


Hat* Character::throwHat()
{
	if (hatQueue.size() != 0) {
		Hat* hatToThrow = hatQueue.front();
		hatQueue.pop();
		return hatToThrow;
	}
	return NULL;
}

void Character::fetchHat(Hat* hat)
{
	if (hatQueue.size() < 10) {
		hatQueue.push(hat);
	}
}
