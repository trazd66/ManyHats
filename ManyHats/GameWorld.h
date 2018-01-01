#include <iostream>
#include"Character.h"
#include"Hat.h"
#include"Platform.h"
#include <list>

using std::list;

class GameWorld {
	//provides simple physics, generates the gameworld
private:
	const static int GRAVITY = -10; // gravity pull for the game world

	double playerHitBox[2] = {2.5,5}; //the hitBoxes of players, depend on the sprite
	const double mapSize[2] = { 800,600 };
	double continentHitBox[2] = { mapSize[0] ,mapSize[1] / 8 };

	list<Character> charList;
	list<Platform> platformList;
	//list<Hat> hatList;


	void ramdonGenPlatform();

	void randomGenHats();

public:
	GameWorld();
	~GameWorld();

	void initiate();//initialize a game world
	
	void initChars(int numOfPlayers = 2);//initiate characters
	
	void dropHats();// drops hats
};