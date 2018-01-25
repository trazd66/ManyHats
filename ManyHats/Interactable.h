#pragma once
#include "Platform.h"
#include <vector>

class Interactable : public InGameObj
{
public:
	Interactable(vec2 hitBox) :InGameObj(hitBox) {};

	// Returns the next vertical speed to adopt, which changes based on whether or not the character is near a platform.
	int getNextYSpeed(std::vector<Platform*> platformList, int gravity)
	{
		// TODO: Fix the bug and change the jumping behaviour.

		int newVerticalSpeed = getY_vel() + gravity;

		if (!getAirborneStatus() && goingDown) {
			goingDown = false;
			setAirborneStatus(true);
			return -1;
		}

		setAirborneStatus(true);

		Platform* currentPlatform;
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

	void setGoingDown(bool status) {
		goingDown = status;
	}
	
	bool getGoingDown() {
		return goingDown;
	}
private:

	// Represents whether the character is trying to go down to the next platform.
	bool goingDown = false;

};

