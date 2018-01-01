#pragma once
#include"InGameObj.h"
#include "Hat.h"
#include <queue>

using std::queue;

class Character :public InGameObj{

private:
	int health = 100;//health of this character, initially set to 100

	int jumpSpeed;// how high this character can jump

	int movementSpeed; //how fast this character can move

	const int playerNum;//player number of this character

	queue<Hat*> hatQueue; // a player can hold up to maximum of 10 hats

public:
	Character(const int playerNum, double(&hitBox)[2]);

	string getItemType() {
		return "Character";
	};

	int getJumpSpeed() {
		return jumpSpeed;
	}

	int getHealth()//returns the health of this character
	{
		return health;
	}

	void setHealth(int num);//set the health of this character

	
	virtual void jump();

	virtual void moveLeft();

	virtual void moveRight();

	virtual Hat* throwHat();

	virtual void fetchHat(Hat* hat);
};