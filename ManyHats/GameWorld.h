#pragma once
#include <iostream>
#include"Character.h"
#include"Hat.h"
#include"Platform.h"
#include <list>

using std::vector;

class GameWorld {
	// Provides simple physics, generates the gameworld.
private:
	// Gravity pull for the game world.
	const static int GRAVITY = -1;

	// The size of this map.
	const double MAP_SIZE[2] = { 800, 600 };


	// The number of platforms in the game.
	// By default, this is one, since the continentHitBox is always in the list of platforms.
	int numPlatforms = 1;

	// The number of hats that must be drawn.  Should be equal to the number of hats in the array.
	int numHats = 0;

	// The hitBoxes of players, depend on the sprite.
	double playerHitBox[2] = { 5, 10 };

	double continentHitBox[2] = { MAP_SIZE[0], MAP_SIZE[1] / 8 };

	// A list containing the characters in this game.
	vector<Character*> charList;

	// A list containing the platforms in this game.
	vector<Platform*> platformList;

	// An array containing the hats in this game.
	Hat* hatArray[50];

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

	// Returns the list of characters in the game.
	vector<Character*> getCharacters();

	// Returns the value of GRAVITY.
	static int getGravity() {
		return GRAVITY;
	}
};