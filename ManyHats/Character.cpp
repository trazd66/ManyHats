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
Character::Character(const int Num, vec2 hitBox) : playerNum(Num), InGameObj(hitBox)
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
	/* TODO:  I wrote in to subtract 40 since it makes it look good.
	 * But in the future, it should probably depend on just the hitbox.
	 * At this point, I think there is something wrong with the hitboxes,
	 * so try to fix this once the hitboxes are working better.
	 */
	if (getLocation()[0] - getHitBox()[0] - 40 <= 0) {
		InGameObj::setX_vel(0);
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
}

// Allows the character to throw a hat.
Hat* Character::throwHat()
{
	if (this->hasHat()) {
		Hat* hatToThrow = hatQueue.front();
		hatQueue.pop();
		hatToThrow->hatOnChar(false);
		hatToThrow->setPlayerThrown(true);
		return hatToThrow;
		// TODO:  Actually throw the hat.
	}
	return nullptr;
}

// Adds a hat to the character's hat queue.
void Character::fetchHat(Hat* hat)
{
	if (hatQueue.size() < 10) {
		hatQueue.push(hat);
		hat->setLocation(
			this->getLocation()[0], 
			this->getLocation()[1] + (hat->getHitBox().y)*hatQueue.size());//hats will be stacking on top of this char's head
		hat->hatOnChar(true);
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
{//TODO: fix the bug and change the jumping behaviour
	Platform* currentPlatform;
	int newVerticalSpeed = getY_vel() + gravity;
	setAirborneStatus(true);
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
			
			/*} else if (newVerticalSpeed >= 0
				&& getLocation()[1] + (getHitBox()[1] / 2.0) <= currentPlatform->getLocation()[1] - (currentPlatform->getHitBox()[1] / 2.0)
				&& getLocation()[1] + (getHitBox()[1] / 2.0) + newVerticalSpeed > currentPlatform->getLocation()[1] - (currentPlatform->getHitBox()[1] / 2.0)) {

				// Adjusts new vertical speed.
				newVerticalSpeed = currentPlatform->getLocation()[1] - (currentPlatform->getHitBox()[1] / 2.0) - getLocation()[1] + (getHitBox()[1] / 2.0);
				*/
			}
		}
	}
	return newVerticalSpeed;
}
