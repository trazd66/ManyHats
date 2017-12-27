#include "GameWorld.h"

void GameWorld::initiate()
{
}

void GameWorld::initChars(int numOfPlayers)
{
	char1 = new Character(1, playerHitBox);
	char2 = new Character(2, playerHitBox);
}


void GameWorld::dropHats()
{
}
