#include "Character.h"
#include "GameWorld.h"

using std::vector;

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
void Character::update(vector<Platform*> platformList, int gravity)
{
	// Set the character's yspeed so that they can interact with the platforms.
	setY_vel(getNextYSpeed(platformList, gravity));

	// Updates the location of this Character object.
	InGameObj::update();
}

// Returns the next vertical speed to adopt, which changes based on whether or not the character is near a platform.
int Character::getNextYSpeed(std::vector<Platform*> platformList, int gravity)
{
	Platform* currentPlatform;
	int newVerticalSpeed = getY_vel() + gravity;
	for (int i = 0; i < platformList.size(); i++) {
		currentPlatform = platformList[i];

		// Checks whether the player is directly on top or below currentPlatform.
		if (getLocation()[0] + (getHitBox()[0] / 2.0) > currentPlatform->getLocation()[0] - (currentPlatform->getHitBox()[0] / 2.0)
			&& getLocation()[0] - (getHitBox()[0] / 2.0) < currentPlatform->getLocation()[0] + (currentPlatform->getHitBox()[0] / 2.0)) {

			// Checks if the character is moving down and the character's feet are above the platform's top and,
			// after taking another step, the character's feet will be below the platform's top.
			if (newVerticalSpeed < 0
				&& getLocation()[1] - (getHitBox()[1] / 2.0) >= currentPlatform->getLocation()[1] + (currentPlatform->getHitBox()[1] / 2.0)
				&& getLocation()[1] - (getHitBox()[1] / 2.0) + newVerticalSpeed < currentPlatform->getLocation()[1] + (currentPlatform->getHitBox()[1] / 2.0)) {

				// Set airborne status to false.
				setAirborneStatus(false);

				// Adjusts new vertical speed.
				newVerticalSpeed = currentPlatform->getLocation()[1] + (currentPlatform->getHitBox()[1] / 2.0) - getLocation()[1] + (getHitBox()[1] / 2.0);

			// Checks if the character is moving up and the character's head is below the platform's bottom and,
			// after taking another step, the character's head will be above the platform's bottom.
			} else if (newVerticalSpeed >= 0
				&& getLocation()[1] + (getHitBox()[1] / 2.0) <= currentPlatform->getLocation()[1] - (currentPlatform->getHitBox()[1] / 2.0)
				&& getLocation()[1] + (getHitBox()[1] / 2.0) + newVerticalSpeed > currentPlatform->getLocation()[1] - (currentPlatform->getHitBox()[1] / 2.0)) {

				// Adjusts new vertical speed.
				newVerticalSpeed = currentPlatform->getLocation()[1] - (currentPlatform->getHitBox()[1] / 2.0) - getLocation()[1] + (getHitBox()[1] / 2.0);
			}
		}
	}
	return newVerticalSpeed;
}
