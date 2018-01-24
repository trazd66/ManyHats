#include "GameWorld.h"

// Constructs a GameWorld object.
GameWorld::GameWorld()
{
}

// Destructs a GameWorld object.
GameWorld::~GameWorld()
{
	// Delete all platforms.
	// Delete all characters.
	// Delete all hats.
}

// Initializes the game.
void GameWorld::initiate()
{
	Platform* floor = new Platform(0, 200, continentHitBox);
	floor->setImage("red.jpg");
	platformList.push_back(floor);
	// generatePlatform(200, 200, 300.0, 25.0);
	// generatePlatform(600, 200, 300.0, 25.0);
	// generatePlatform(400, 400, 300.0, 25.0);

	// Coordinates:   x1   y1   x2   y2
	int coords[4] = { 200, 350, 300, 400 };
	initChars(coords, 2);
}

// Updates the game.
void GameWorld::update()
{
	for (int i = 0; i < charList.size(); i++) {
		charList[i]->update(this->platformList, GRAVITY);
	}

	// for (int i = 0; i < platformList.size(); i++) {
	// 	for (int j = 0; j < charList.size(); j++) {

	// 		if (charList[j]->touching(*(platformList[i]))) {

	// 			if (charList[j]->getLocation()[1] - (charList[j]->getHitBox()[1] / 2.0) - charList[j]->getY_vel() >= platformList[i]->getLocation()[1] + (platformList[i]->getHitBox()[1] / 2.0)) {
	// 				// Above the platform.
	// 				charList[j]->setY_vel(0);
	// 				charList[j]->setLocation(charList[j]->getLocation()[0], platformList[i]->getLocation()[1] + (platformList[i]->getHitBox()[1] + charList[j]->getHitBox()[1]) / 2.0 + 1);
	// 				charList[j]->setAirborneStatus(false);
	// 			} else if (charList[j]->getLocation()[1] + (charList[j]->getHitBox()[1] / 2.0) + charList[j]->getY_vel() <= platformList[i]->getLocation()[1] - (platformList[i]->getHitBox()[1] / 2.0)) {
	// 				// Below the platform.
	// 				charList[j]->setY_vel(0);
	// 				charList[j]->setLocation(charList[j]->getLocation()[0], platformList[i]->getLocatio	n()[1] - (platformList[i]->getHitBox()[1] + charList[j]->getHitBox()[1]) / 2.0);
	// 				// Should not be necessary to set airborne status to true, but do it just in case.
	// 				charList[j]->setAirborneStatus(true);
	// 			} else {
	// 				// On the same level as the platform.
	// 				charList[j]->setLocation(charList[j]->getLocation()[0] - charList[j]->getX_vel(), charList[j]->getLocation()[1]);
	// 			}
	// 		// } else {
	// 		// 	if (!(charList[j]->getLocation()[0] - (charList[j]->getHitBox()[0] / 2.0) < platformList[i]->getLocation()[0] + (platformList[i]->getHitBox()[0] / 2.0) &&
	// 		// 		charList[j]->getLocation()[0] + (charList[j]->getHitBox()[0] / 2.0) > platformList[i]->getLocation()[0] - (platformList[i]->getHitBox()[0] / 2.0))) {
	// 		// 		// Not horizontally colliding.
	// 		// 		// Also, check whether they are above the platform.
	// 		// 	}
	// 		}
	// 	}
	// }
}

// Initializes the characters in this game.
void GameWorld::initChars(int* coords, int numOfPlayers)
{
	for (int i = 0; i < numOfPlayers; i++) {
		Character* thisChar = new Character(i + 1, playerHitBox);
		thisChar->setLocation(coords[2 * i], coords[2 * i + 1]);
		charList.push_back(thisChar);
	}
}

// Randomly drop the generated hats to players.
void GameWorld::dropHats()
{

}

// Generate the world's platforms randomly.
void GameWorld::randomGenPlatform()
{
	// First generate the main continent.
	Platform* continent = new Platform(400, 0, continentHitBox);
	platformList.push_back(continent);
	// TODO:  Then generate mario-like islands that players can jump to.

}

// Generate a single platform in this game.
void GameWorld::generatePlatform(int x, int y, double width, double height)
{
	double hitBox[2] = { width, height };
	platformList.push_back(new Platform(x, y, hitBox));
	numPlatforms++;
}

// Randomly generate different kinds of hats.
void GameWorld::randomGenHats()
{

}

// Returns the list of characters in the game.
vector<Character*> GameWorld::getCharacters()
{
	return charList;
}
