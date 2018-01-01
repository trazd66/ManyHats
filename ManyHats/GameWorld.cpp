#include "GameWorld.h"

GameWorld::GameWorld()
{
}

GameWorld::~GameWorld()
{
	//delete all platforms
	//delete all characters
	//delete all hats
}

void GameWorld::initiate()
{
}

void GameWorld::initChars(int numOfPlayers)
{
	for (int i = 0; i++; i < numOfPlayers) {
		Character* thisChar = new Character(i + 1, playerHitBox);
		charList.push_back(*thisChar);
	}
}


void GameWorld::dropHats()
{
	//randomly drop the generated hats to players
}

void GameWorld::ramdonGenPlatform()
{
	//first generate the main continent
	Platform* continent = new Platform(continentHitBox);
	platformList.push_back(*continent);
	// then generate mario-like islands that players can jump to

}

void GameWorld::randomGenHats()
{
	//randomly generate different kinds of hats
}
