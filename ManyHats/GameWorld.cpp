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
	generatePlatform(400, 50, MAP_SIZE.x/2, 25.0);

	// Generate three more platforms.
	generatePlatform(300, 100, 200.0, 25.0);
	generatePlatform(100, 200, 200.0, 25.0);
	
	// TODO:  Make this randomized, if there is time.

}

// Generate a single platform in this game.
void GameWorld::generatePlatform(int x, int y, double width, double height)
{
	Platform* p = new Platform(x, y, glm::vec2( width, height ));
	p->setImage("red.jpg");
	platformList.push_back(p);
	numPlatforms++;
}

void GameWorld::updateHatStatus()
{
	for (auto hat : this->currRenderedHats) {
		for (auto player : this->charList) {
			if (hat->getThrownStatus()!= 0 && 
				hat->getThrownStatus()!= player->getPlayerNum() &&
				hat->touching(*player)) {

				player->setHealth(player->getHealth() - hat->getBaseDamage());
				hat->setRenderStatus(false); // should no longer be rendered
				hat->setPlayerThrown(0); //no longer thrown by a player

			}
			else {
				hat->setX_vel(hat->getX_vel());
				hat->setY_vel(hat->Interactable::getNextYSpeed(platformList,GRAVITY));
				hat->InGameObj::update();
			}
		}
	}
}

// Randomly generate different kinds of hats.
void GameWorld::randomGenHats()
{

}
