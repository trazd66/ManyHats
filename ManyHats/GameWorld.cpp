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
	platformList.push_back(*(new Platform(0, 0, continentHitBox)));
	generatePlatform(200, 200, 300.0, 25.0);
	generatePlatform(600, 200, 300.0, 25.0);
	generatePlatform(400, 400, 300.0, 25.0);
	initChars(2);
}

// Initializes the characters in this game.
void GameWorld::initChars(int numOfPlayers)
{
	for (int i = 0; i < numOfPlayers; i++) {
		Character* thisChar = new Character(i + 1, playerHitBox);
		charList.push_back(*thisChar);
	}
}

// Randomly drop the generated hats to players.
void GameWorld::dropHats()
{

}

// Generate the world's platforms randomly.
void GameWorld::ramdonGenPlatform()
{
	// First generate the main continent.
	Platform* continent = new Platform(0, 0, continentHitBox);
	platformList.push_back(*continent);
	// TODO:  Then generate mario-like islands that players can jump to.

}

// Generate a single platform in this game.
void GameWorld::generatePlatform(int x, int y, double width, double height)
{
	double hitBox[2] = { width, height };
	platformList.push_back(*(new Platform(x, y, hitBox)));
	numPlatforms++;
}

// Randomly generate different kinds of hats.
void GameWorld::randomGenHats()
{

}
