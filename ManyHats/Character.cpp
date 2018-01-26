#include "Character.h"
#include "GameWorld.h"

using std::vector;

// Sets the character's health.
void Character::setHealth(int num)
{
	if (0 <= num && num <= 100) {
		num = num;
	}
	else if (num > 100) {
		num = 100;
	}
	else {
		num = 0;
	}
}

void Character::updateHatLocation()
{
	for (int i = 0; i < hatQueue.size(); i++) {
		hatQueue[i]->setLocation(
			this->getLocation()[0],
			this->getLocation()[1] + this->getHitBox().y*3.5 + (hatQueue[i]->getHitBox().y)*5*i);
	}
}

// Default constructor for a Character object.
Character::Character(const int Num, vec2 hitBox) : playerNum(Num), Interactable(hitBox)
{
	// The jump speed is set to be double the character's height.
	setJumpSpeed((int) getHitBox()[1] /1.0f);

	// The movement speed is set to be double the width.
	// setMovementSpeed((int) getHitBox()[0] * 2);
	setMovementSpeed(7);
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
	isMoving = true;
	InGameObj::setX_vel(-movementSpeed);
	if (getLocation()[0] - getHitBox()[0]<= 0) {
		InGameObj::setX_vel(0);
	}
	for (auto hat : this->hatQueue) {
		hat->setFaceRight(false);
	}
}

// Move the character to the right.
void Character::moveRight()
{
	faceRight = true;
	isMoving = true;
	InGameObj::setX_vel(movementSpeed);
	if (getLocation()[0] + getHitBox()[0] >= 800) {
		InGameObj::setX_vel(0);
	}
	for (auto hat : this->hatQueue) {
		hat->setFaceRight(true);
	}
}

// Allows the character to throw a hat.
Hat* Character::throwHat()
{
	if (this->hasHat()) {
		Hat* hatToThrow = hatQueue.front();
		hatQueue.pop_front();//removes the first element
		hatToThrow->hatOnChar(false);
		hatToThrow->setPlayerThrown(this->getPlayerNum());
		return hatToThrow;
		// TODO:  Actually throw the hat.
	}
	return nullptr;
}

// Adds a hat to the character's hat queue.
void Character::fetchHat(Hat* hat)
{
	if (hatQueue.size() < 10) {
		hatQueue.push_back(hat);
		hat->setLocation(
			this->getLocation()[0], 
			this->getLocation()[1] + (hat->getHitBox().y)*hatQueue.size());//hats will be stacking on top of this char's head
		hat->hatOnChar(true);
	}
}

void Character::killCharacter() {
	setHealth(100);
	setLocation(300, 20000);
	if (getLives() > 0) {
		setLives(getLives() - 1);
	}
}

// Update this object.
void Character::update(vector<Platform*> platformList, int gravity)
{
	// Set the character's yspeed so that they can interact with the platforms.
	setY_vel(Interactable::getNextYSpeed(platformList, gravity));

	// Updates the location of this Character object.
	InGameObj::update();

	// Update all the hat locations
	this->updateHatLocation();

	if (getLocation()[1] < -60) {
		killCharacter();
	}
}

