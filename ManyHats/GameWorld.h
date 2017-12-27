#include <iostream>
#include"Character.h"
#include"Hat.h"

class GameWorld {
	//provides simple physics, generates the gameworld
private:
	const static int GRAVITY = -10; // gravity pull for the game world

	double playerHitBox[2] = {2.5,5};
	
	Character* char1;
	Character* char2;

public:
	void initiate();//initialize a game world
	
	void initChars(int numOfPlayers = 2);//initiate characters
	
	void dropHats();// drops hats
};