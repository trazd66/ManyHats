#pragma once
#include <iostream>
#include "Character.h"

//hats
#include "BaseballCap.h"
#include "ChiefHat.h"
#include "BombHat.h"
#include "NurseHat.h"
#include "SantaHat.h"

#include "Platform.h"
#include <vector>
#include <deque>
//hats

using std::vector;

// Provides simple physics, generates the gameworld.
class GameWorld {
private:
	// Gravity pull for the game world.
	const static int GRAVITY = -1;

	// The size of this map.
	const vec2 MAP_SIZE = { 800, 600 };


	/* The number of platforms in the game.
	 * By default, this is zero, since it increases whenever generatePlatform() is called.
	 */
	int numPlatforms = 0;

	// The number of hats that must be drawn.  Should be equal to the number of hats in the array.
	int numHats = 0;

	// The hitBoxes of players, depend on the sprite.(the ratiao  x:y = 1:2.5)
	vec2  playerHitBox = {6.28, 15.7};

	// A list containing the characters in this game.
	vector<Character*> charList;

	// A list containing the platforms in this game.
	vector<Platform*> platformList;

	// An array containing the hats in this game.
	std::deque<Hat*> containedHats;

	// Randomly generates the game's platforms.
	void randomGenPlatform();

	// Randomlty generates the hats in the game.
	void randomGenHats();

public:

	// Constructor.
	GameWorld();

	// Destructor.
	~GameWorld();

	// Initialize a game world.
	void initiate();

	// Update the game world.
	void update();

	// Initiate characters.
	void initChars(int* coords, int numOfPlayers = 2);

	// Initiates the hat dropping.
	void dropHats();

	// Generates a single platform.
	void generatePlatform(int x, int y, double width, double height);

	// Returns the list of platforms in the game.
	vector<Platform*> getPlatforms()
	{
		return platformList;
	}

	// Returns the list of characters in the game.
	vector<Character*> getCharacters() {
		return this->charList;
	}

	// returns the list of hats this world has
	std::deque<Hat*> getHats() {
		return this->containedHats;
	}

	// Returns the value of GRAVITY.
	static int getGravity() {
		return GRAVITY;
	}

	void updateHatStatus();
};
