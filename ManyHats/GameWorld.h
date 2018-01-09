#pragma once
#include <iostream>
#include"Character.h"
#include"Hat.h"
#include"Platform.h"
#include <list>

using std::list;

class GameWorld {
	// Provides simple physics, generates the gameworld.
private:
	// Gravity pull for the game world.
	const static int GRAVITY = -10;

	// The size of this map.
	const double MAP_SIZE[2] = { 800, 600 };

	// The number of platforms in the game.
	int numPlatforms;

	// The hitBoxes of players, depend on the sprite.
	double playerHitBox[2] = { 5, 10 };

	double continentHitBox[2] = { MAP_SIZE[0], MAP_SIZE[1] / 8 };

	// A list containing the characters in this game.
	list<Character> charList;

	// A list containing the platforms in this game.
	list<Platform> platformList;

	// An array containing the hats in this game.
	Hat* hatArray[50];

	void ramdonGenPlatform();

	// Randomlty generates the hats in the game.
	void randomGenHats();

public:
	// Constructor.
	GameWorld();

	// Destructor.
	~GameWorld();

	// Initialize a game world.
	void initiate();

	// Initiate characters.
	void initChars(int numOfPlayers = 2);

	// Initiates the hat dropping.
	void dropHats();

	// Generates a single platform.
	void generatePlatform(int x, int y, int width, int height);
};