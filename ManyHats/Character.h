#pragma once
#include"InGameObj.h"
#include "Hat.h"
#include <queue>

using std::queue;

// A class representing a character in this game.
class Character : public InGameObj {

private:
	// The health of this character, initially set to 100.
	int health = 100;

	// The initial jump speed of this character.
	int jumpSpeed;

	// How fast this character can move.
	int movementSpeed;

	// Player number of this character.
	const int playerNum;

	// The queue of hats held by the player.
	// A player can hold up to maximum of 10 hats.
	queue<Hat*> hatQueue;

	// True if facing right (default), false if left.
	bool faceRight = true;

public:
	// The default constructor for Character objects.
	Character(const int playerNum, double(&hitBox)[2]);

	// Returns the type of this object.
	string getItemType() {
		return "Character";
	};

	// Returns the initial jump speed of this character.
	int getJumpSpeed() {
		return jumpSpeed;
	}

	// Sets the initial jump speed of this character.
	void setJumpSpeed(int newSpeed) {
		jumpSpeed = newSpeed;
	}

	// Returns the movement speed of this character.
	int getMovementSpeed() {
		return movementSpeed;
	}

	// Sets the movement speed of this character.
	void setMovementSpeed(int newSpeed) {
		movementSpeed = newSpeed;
	}

	// Returns the health of this character.
	int getHealth()
	{
		return health;
	}
	// Set the health of this character.
	// Precondition:  0 <= num <= 100.
	void setHealth(int num);

	// Returns whether the player is facing right.
	bool ifFaceRight() {
		return faceRight;
	}

	// Updates the Character.
	void update();

	// Initiates a jump.
	virtual void jump();

	// Moves the player slightly to the left.
	virtual void moveLeft();

	// Moves the player slightly to the right.
	virtual void moveRight();

	// Allows the player to throw a hat.
	virtual Hat* throwHat();

	// Adds a hat to the character's hat queue.
	virtual void fetchHat(Hat* hat);
};