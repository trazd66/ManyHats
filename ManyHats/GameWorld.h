#pragma once
#include <iostream>
#include "Character.h"
#include "Hat.h"
#include "Platform.h"
#include <vector>
using std::vector;

// Provides simple physics, generates the gameworld.
class GameWorld {	
private:
	// Gravity pull for the game world.
	const static int GRAVITY = -1;

	// The size of this map.
	const double MAP_SIZE[2] = { 800, 600 };


	/* The number of platforms in the game.
	 * By default, this is zero, since it increases whenever generatePlatform() is called.
	 */
	int numPlatforms = 0;

	// The number of hats that must be drawn.  Should be equal to the number of hats in the array.
	int numHats = 0;

	// The hitBoxes of players, depend on the sprite.
	double playerHitBox[2] = { 5, 10 };

	// A list containing the characters in this game.
	vector<Character*> charList;

	// A list containing the platforms in this game.
	vector<Platform*> platformList;

	// An array containing the hats in this game.
	Hat* hatArray[50];

	// True iff game is meant to be paused.  False by default.
	bool gameIsPaused = false;

	void randomGenPlatform();

	// Randomlty generates the hats in the game.
	void randomGenHats();

	/* Represents whether the game is ready to be paused 
	 * (i.e. whether the escape key has been released).
	 */
	bool readyToBePaused = true;

	// The last locations of the characters before the game is paused.
	std::vector<double> lastLocations;

	// The last speeds of the characters before the game is paused.
	std::vector<int> lastSpeeds;

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
	vector<Character*> getCharacters();

	// Returns the value of GRAVITY.
	static int getGravity() {
		return GRAVITY;
	}

	// Sets the game to be paused or to continue.
	void setPaused(bool newValue) {
		gameIsPaused = newValue;
	}

	// Returns whether the game is meant to be paused.
	bool getPaused() {
		return gameIsPaused;
	}

	// Sets the variable representing whether or not the game is ready to be paused.
	void setReadyToBePaused(bool newValue) {
		readyToBePaused = newValue;
	}

	// Returns whether the game is ready to be paused.
	bool getReadyToBePaused() {
		return readyToBePaused;
	}
};