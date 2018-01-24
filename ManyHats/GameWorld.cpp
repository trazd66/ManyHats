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
	randomGenPlatform();

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
	generatePlatform(400, 0, MAP_SIZE[0], MAP_SIZE[1] / 8);

	// Generate three more platforms.
	generatePlatform(200, 200, 300.0, 25.0);
	generatePlatform(600, 200, 300.0, 25.0);
	generatePlatform(400, 400, 300.0, 25.0);
	
	// TODO:  Make this randomized, if there is time.

}

// Generate a single platform in this game.
void GameWorld::generatePlatform(int x, int y, double width, double height)
{
	double hitBox[2] = { width, height };
	Platform* p = new Platform(x, y, hitBox);
	p->setImage("red.jpg");
	platformList.push_back(p);
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

// Stores the current state of the game's characters before it is paused.
void GameWorld::storeCharacterStates() {
	if (lastLocations.size() != 4 || lastSpeeds.size() != 4) {
		lastLocations.push_back(charList[0]->getLocation()[0]);
		lastLocations.push_back(charList[0]->getLocation()[1]);
		lastLocations.push_back(charList[1]->getLocation()[0]);
		lastLocations.push_back(charList[1]->getLocation()[1]);

		lastSpeeds.push_back(charList[0]->getX_vel());
		lastSpeeds.push_back(charList[0]->getY_vel());
		lastSpeeds.push_back(charList[1]->getX_vel());
		lastSpeeds.push_back(charList[1]->getY_vel());
	}
	else {
		lastLocations[0] = charList[0]->getLocation()[0];
		lastLocations[1] = charList[0]->getLocation()[1];
		lastLocations[2] = charList[1]->getLocation()[0];
		lastLocations[3] = charList[1]->getLocation()[1];

		lastSpeeds[0] = charList[0]->getX_vel();
		lastSpeeds[1] = charList[0]->getY_vel();
		lastSpeeds[2] = charList[1]->getX_vel();
		lastSpeeds[3] = charList[1]->getY_vel();
	}
}

/* Restores the character states after the game is unpaused.
 * If either of the vectors for lastLocations or lastSpeeds are not 
 * correct, then they will be set to default values for all entries.
 */
void GameWorld::restoreCharacterStates() {
	if (lastLocations.size() != 4 || lastSpeeds.size() != 4) {
		storeCharacterStates();
		return;
	}
	charList[0]->setLocation(lastLocations[0], lastLocations[1]);
	charList[1]->setLocation(lastLocations[2], lastLocations[3]);

	charList[0]->setVelocity(lastSpeeds[0], lastSpeeds[1]);
	charList[1]->setVelocity(lastSpeeds[2], lastSpeeds[3]);
}

/* Returns the distance between the character now and the character a 
 * few milliseconds ago.  This function is being used to prevent a
 * strange bug in the pause functionality.
 * Note:  - charNo is the index (0 or 1) of the character in the charList.
 */
int GameWorld::distanceLastTravelled(int charNo) {
	if (lastLocations.size() != 4 || lastSpeeds.size() != 4) {
		std::cout << "Checkpoint 1\n";
		storeCharacterStates();
		return 0;
	}
	return std::sqrt(std::pow(lastLocations[2 * charNo] - charList[charNo]->getLocation()[0], 2) + 
		std::pow(lastLocations[2 * charNo + 1] - charList[charNo]->getLocation()[1], 2));
}
