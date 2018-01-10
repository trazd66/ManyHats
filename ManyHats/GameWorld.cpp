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
}

// Updates the game.
void GameWorld::update()
{
	for (int i = 0; i < charList.size(); i++) {
		charList[i]->update();
	}

	for (int i = 0; i < platformList.size(); i++) {
		for (int j = 0; j < charList.size(); j++) {

			if (charList[j]->touching(*(platformList[i]))) {
				charList[j]->setY_vel(0);
				charList[j]->setLocation(charList[j]->getLocation()[0], platformList[i]->getLocation()[1] + (platformList[i]->getHitBox()[1] + charList[j]->getHitBox()[1]) / 2.0);
				charList[j]->setAirborneStatus(false);
			}
		}
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
	charList[0]->setImage("MarioTest.png");
	charList[1]->setImage("LuigiTest.png");
}

// Randomly drop the generated hats to players.
void GameWorld::dropHats()
{

}

// Generate the world's platforms randomly.
void GameWorld::randomGenPlatform()
{

}

// Generate a single platform in this game.
void GameWorld::generatePlatform(int x, int y, double width, double height)
{

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
