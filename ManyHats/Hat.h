#pragma once // Can CDH sort this out?  -Papa Dylan
#include "Interactable.h"

// Represents a Hat in the game.
class Hat : public Interactable {
public:
	// The default constructor for this class.
	Hat(const int baseDamage, const double damageModifier, const double fallSpeed, const double launchSpeed, vec2 hitBox, int pos)
		: baseDamage(baseDamage), damageModifier(damageModifier), fallSpeedModifier(fallSpeed), launchVelocity(launchSpeed), Interactable(hitBox),spritePosition(pos)
	{};

	// The default destructor for this class.
	~Hat() {
		delete & baseDamage;
		delete & damageModifier;
		delete & fallSpeedModifier;
		delete & launchVelocity;
		delete & playerThrown;
	};

	// Returns the baseDamage of the hat.
	int getBaseDamage() {
		return this->baseDamage;
	};

	// Returns the damage modifier of the hat.
	double getDamageModifier() {
		return this->damageModifier;
	};

	// Returns the fall speed of the hat.
	double getFallSpeed() {
		return this->fallSpeedModifier;
	};

	// Returns the launch velocity of the hat.
	double getLaunchVelocity() {
		return this->launchVelocity;
	};

	// Returns the player number that throw this hat
	int getThrownStatus() {
		return playerThrown;
	}

	// True if the hat is thrown by a player, false otherwise.
	void setPlayerThrown(int playerNum) {
		playerThrown = playerNum;
	}

	// Set the status of the hat (that if it's being carried by a character)
	void setCharNum(int newNum) {
		charNum = newNum;
	}
	
	int getCharNum() {
		return this->charNum;
	}

	virtual void launch() = 0;

	/*set the render status of this hat*/
	void setRenderStatus(bool status) {
		this->render = status;
	}

	/*true if this hat is being rendered */
	bool getRenderStatus() {
		return render;
	}

	void setFaceRight(bool faceRight) {
		this->faceRight = faceRight;
	}

	bool getFaceRight() {
		return faceRight;
	}
	
	//the position of this hat on the sprite sheet
	int getSpritePosition() {
		return spritePosition;
	}

	virtual void reset() = 0;
private:
	int spritePosition;

	//direction this hat is facing
	bool faceRight = true;

	/* When the hat is carried by a character, the hat moves with the character.
	0 means not on a character, 1 means on Player 1, 2 means on Player 2.
	*/
	int charNum = 0;

	/*true if this hat is being rendered */
	bool render = false;

	//the default launch status for this
	glm::vec2 launchStatus;

	// The base damage of the hat.
	const int baseDamage;

	// The damage modifier of the hat.
	const double damageModifier;

	// The fall speed of the hat (when it's airborne).
	const double fallSpeedModifier;

	// The launch velocity of the hat.
	const double launchVelocity;

	// Represents whether or not the hat is thrown by a player.
	// The number is the player's number.
	// 0 means not being thrown.
	int playerThrown = 0;
};