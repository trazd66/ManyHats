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

	randomGenHats();
}

// Updates the game.
void GameWorld::update()
{
	for (int i = 0; i < charList.size(); i++) {
		charList[i]->update(this->platformList, GRAVITY);
	}
	dropHats();
	this->updateHatStatus();
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
	for (auto hat : this->getNonRenderedHats()) {
		hat->setLocation(100, 500);
		hat->setRenderStatus(true);
		this->nonRenderedHat.pop_front();
		this->currRenderedHats.push_back(hat);
	}
}

// Generate the world's platforms randomly.
void GameWorld::randomGenPlatform()
{
		
	// First generate the main continent.
	generatePlatform(400, 50, MAP_SIZE.x * 0.9, 25.0);

	// Generate three more platforms.
	generatePlatform(200, 200, 200.0, 25.0);
	generatePlatform(600, 200, 200.0, 25.0);
	generatePlatform(425, 400, 250.0, 25.0);
	
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
	for (auto theHat : this->currRenderedHats) {
		for (auto player : this->charList) {
			if (theHat->getThrownStatus() != 0 &&
				theHat->getThrownStatus() != player->getPlayerNum() &&
				theHat->touching(*player)) {
				// when this hat hit a character
				player->setHealth(player->getHealth() - theHat->getBaseDamage());
				theHat->setRenderStatus(false); // should no longer be rendered
				theHat->setPlayerThrown(0); //no longer thrown by a player
				this->nonRenderedHat.push_back(theHat);
				this->currRenderedHats.pop_front();
			}
			else if (theHat->getThrownStatus() == 0 && theHat->touching(*player) && !theHat->getOnCharStatus()) {
				player->fetchHat(theHat);
			} else {//when this hat is thrown and flying (did not hit anyone)
				theHat->setY_vel(theHat->Interactable::getNextYSpeed(platformList, GRAVITY));
				if (theHat->getY_vel() < -1) {
					theHat->setY_vel(-1);
				}
				theHat->InGameObj::update();
			}
		}
	}
}

// Randomly generate different kinds of hats.
void GameWorld::randomGenHats()
{
	for (int i = 0; i < 10; i++) {
		this->nonRenderedHat.push_back(new BaseballCap(vec2(5,5)));
	}
}
