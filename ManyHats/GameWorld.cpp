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

	// This code allows players to push other players.
	/*int newXVel = 30;
	if (getCharacters()[0]->touching(*getCharacters()[1])) {
		for (int i = 0; i < getCharacters().size(); i++) {
			// Set the other character number to whatever i is not.
			int j = (i == 0) ? 1 : 0;
			if (getCharacters()[i]->getX_vel() > 0 &&
				getCharacters()[i]->getLocation()[0] < getCharacters()[j]->getLocation()[0] &&
				getCharacters()[j]->getX_vel() == 0) {
				std::cout << "1" << std::endl;
				newXVel = 10;
			}
			else if (getCharacters()[i]->getX_vel() < 0 &&
				getCharacters()[i]->getLocation()[0] > getCharacters()[j]->getLocation()[0] &&
				getCharacters()[j]->getX_vel() == 0) {
				std::cout << "2" << std::endl;
				newXVel = -10;
			} else if (getCharacters()[i]->getX_vel() < 0 &&
				getCharacters()[i]->getLocation()[0] > getCharacters()[j]->getLocation()[0] &&
				getCharacters()[j]->getX_vel() > 0) {
				std::cout << "3" << std::endl;
				newXVel = 0;
			}
		}
	}

	if (newXVel != 30) {
		std::cout << "4" << std::endl;
		getCharacters()[0]->setX_vel(newXVel);
		getCharacters()[1]->setX_vel(newXVel);
	}*/
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
			// The "or" part of the following if statement is there in order to fix the collisions.
			if ((theHat->touching(*player, 0, -40) || theHat->touching(*player)) &&
				theHat->getThrownStatus() != 0 &&
				theHat->getThrownStatus() != player->getPlayerNum()) {

				// when this hat hit a character
				player->setHealth(player->getHealth() - theHat->getBaseDamage());
				
				// Moves the player backwards when hit with a baseball hat.
				// TODO:  Eventually, get it to be a smooth movement.
				if (theHat->getItemType() == "BaseballCap") {
					int movementDistance = (theHat->getX_vel() > 0) ? 40 : -40;
					player->setLocation(player->getLocation()[0] + movementDistance, player->getLocation()[1]);
				} else if (theHat->getItemType() == "SantaHat" && theHat->getY_vel() > 0) {
					player->setY_vel(15);
					// player->setLocation(player->getLocation()[0], player->getLocation()[1] + 50);
				}
				theHat->reset();
			} else if (theHat->touching(*player)
				&& theHat->getThrownStatus() == 0 &&
				theHat->getCharNum() == 0) {
				// catch the hat
				player->fetchHat(theHat);
			} else if (
				theHat->getLocation()[0] < 0 ||
				theHat->getLocation()[0] > MAP_SIZE[0] ||
				theHat->getLocation()[1] < 0 ||
				theHat->getLocation()[1] > MAP_SIZE[1] + 1000) {
				theHat->reset();
			} else if (theHat->getItemType() == "SantaHat" &&
				theHat->getThrownStatus() != 0 &&
				theHat->getY_vel() == 0 &&
				!theHat->getGoingDown()) {
				// If a Santa Hat is at the top of its jump, set its y-speed to make it fall faster.
				theHat->setX_vel(0);
				theHat->setGoingDown(true);
				theHat->setGoDownFaster(true);
			} else {//when this hat is thrown and flying (did not hit anyone)
				theHat->setY_vel(theHat->Interactable::getNextYSpeed(platformList, GRAVITY));
				if (theHat->getY_vel() < -1) {
					theHat->setY_vel(-1);
				}
				if (theHat->shouldGoDownFaster()) {
					theHat->setY_vel(-5);
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
		this->containedHats.push_back(new BaseballCap(vec2(30, 6)));
		// this->containedHats.push_back(new ChiefHat(vec2(6, 6)));
		// this->containedHats.push_back(new BombHat(vec2(6, 6)));
		this->containedHats.push_back(new SantaHat(vec2(30, 6)));
	}

	for (int i = 0; i < 5; i++) {
		this->containedHats.push_back(new NurseHat(vec2(30, 6)));
	}


}
