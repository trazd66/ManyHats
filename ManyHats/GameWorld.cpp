#include "GameWorld.h"
#include <cstdlib>

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
		for (auto hat : this->getHats()) {
			if (rand() % 1000 <= 1 && !hat->getRenderStatus()) {
				hat->setLocation(rand() % 10 * 60, MAP_SIZE[1]);
				hat->setRenderStatus(true);
			}
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
	platformList.push_back(p);
	numPlatforms++;
}

void GameWorld::updateHatStatus()
{
	for (auto theHat : this->containedHats) {
		for (auto player : this->charList) {
			if (theHat->touching(*player)) {
				if (theHat->getThrownStatus() != 0 &&
					theHat->getThrownStatus() != player->getPlayerNum()) {

					// when this hat hit a character
					player->setHealth(player->getHealth() - theHat->getBaseDamage());
					theHat->reset();
				} else if (theHat->getThrownStatus() == 0 && theHat->getCharNum() == 0) {
					// catch the hat
					player->fetchHat(theHat);
				}
			} else if (
				theHat->getLocation()[0] < 0 ||
				theHat->getLocation()[0] > MAP_SIZE[0] ||
				theHat->getLocation()[1] < 0 ||
				theHat->getLocation()[1] > MAP_SIZE[1] + 300) {
	
				theHat->reset();
			}	else {//when this hat is thrown and flying (did not hit anyone)
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
		this->containedHats.push_back(new BaseballCap(vec2(6,6)));
//		this->containedHats.push_back(new ChiefHat(vec2(6, 6)));
	//	this->containedHats.push_back(new BombHat(vec2(6, 6)));
	//	this->containedHats.push_back(new SantaHat(vec2(6, 6)));
	}

	for (int i = 0; i < 5; i++) {
		this->containedHats.push_back(new NurseHat(vec2(6, 6)));
	}


}
