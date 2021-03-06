#include "Character.h"
#include "GameWorld.h"

using std::vector;

// Sets the character's health.
void Character::setHealth(int num)
{
	if (0 <= num && num <= 100) {
		health = num;
	}
	else if (num > 100) {
		health = 100;
	}
	else {
		health = 0;
	}
}

void Character::updateHatLocation()
{
	for (int i = 0; i < hatQueue.size(); i++) {
		hatQueue[i]->setLocation(
			this->getLocation()[0],
			this->getLocation()[1] + 53 + (hatQueue[i]->getHitBox().y)*4*i);
	}
}

// Default constructor for a Character object.
Character::Character(const int Num, vec2 hitBox) : playerNum(Num), Interactable(hitBox)
{
	// The jump speed is set to be double the character's height.
//	setJumpSpeed((int) getHitBox()[1] / 0.7f);
	setJumpSpeed(21);

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
		hatToThrow->setCharNum(0);
		hatToThrow->setPlayerThrown(this->getPlayerNum());
		return hatToThrow;
	}
	return nullptr;
}

// Adds a hat to the character's hat queue.
void Character::fetchHat(Hat* hat)
{
	if (hatQueue.size() < 10 && hat->getThrownStatus() == 0) {
		hat->setCharNum(this->playerNum);
		hat->setFaceRight(faceRight);
		hatQueue.push_back(hat);
	}
}

void Character::killCharacter() {
	setHealth(100);
	setLocation(300, 20000);
	setRestrictXMotion(true);
	if (getLives() > 0) {
		this->setHealth(100);
		setLives(getLives() - 1);
	}
	for (auto hat : this->hatQueue) {
		hat->reset();
		hatQueue.pop_front();
	}
}

// Update this object.
void Character::update(vector<Platform*> platformList, int gravity)
{
	// Set the character's yspeed so that they can interact with the platforms.
	setY_vel(Interactable::getNextYSpeed(platformList, gravity));

	// Updates the location of this Character object.
	InGameObj::update();

	if (getY_vel() == 0 && restrictXMotion) {
		restrictXMotion = false;
	}

	// Update all the hat locations
	this->updateHatLocation();

	if (getLocation()[1] < -60 || this->health <= 0 ) {
		killCharacter();
	}
}

