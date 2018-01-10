#include "Character.h"
#include "GameWorld.h"

// Sets the character's health.
void Character::setHealth(int num)
{
	if (0 <= num && num <= 100) {
		health = num;
	}
}

// Default constructor for a Character object.
Character::Character(const int Num, double(&hitBox)[2]) : playerNum(Num), InGameObj(hitBox)
{
	// The jump speed is set to be double the character's height.
	setJumpSpeed((int) getHitBox()[1] * 2);

	// The movement speed is set to be double the width.
	// setMovementSpeed((int) getHitBox()[0] * 2);
	setMovementSpeed(9);
}

// Make the character jump.
void Character::jump()
{
	if (InGameObj::getAirborneStatus() == false) {
		InGameObj::setAirborneStatus(true);
		InGameObj::setY_vel(jumpSpeed);
	}
}

// Move the character to the right.
void Character::moveLeft()
{
	faceRight = false;
	InGameObj::setX_vel(-movementSpeed);
}

// Move the character to the right.
void Character::moveRight()
{
	faceRight = true;
	InGameObj::setX_vel(movementSpeed);
}

// Allows the character to throw a hat.
Hat* Character::throwHat()
{
	if (hatQueue.size() != 0) {
		Hat* hatToThrow = hatQueue.front();
		hatQueue.pop();
		return hatToThrow;
		// TODO:  Actually throw the hat.
	}
	return NULL;
}

// Adds a hat to the character's hat queue.
void Character::fetchHat(Hat* hat)
{
	if (hatQueue.size() < 10) {
		hatQueue.push(hat);
	}
}

// Update this object.
void Character::update()
{
	InGameObj::update();
	setY_vel(getY_vel() + GameWorld::getGravity());
}
