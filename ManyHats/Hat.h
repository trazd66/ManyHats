#pragma once // Can CDH sort this out?  -Papa Dylan
#include "Interactable.h"

// Represents a Hat in the game.
class Hat : public Interactable {
public:
	// The default constructor for this class.
	Hat(const int baseDamage, const double damageModifier, const double fallSpeed, const double launchSpeed, vec2 hitBox)
		: baseDamage(baseDamage), damageModifier(damageModifier), fallSpeedModifier(fallSpeed), launchVelocity(launchSpeed), Interactable(hitBox)
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

	// Launches the hat with given direction!
	//virtual void launch(double xDir, double yDir) = 0;

	// Returns the player number that throw this hat
	int getThrownStatus() {
		return playerThrown;
	}

	// True if the hat is thrown by a player, false otherwise.
	void setPlayerThrown(int playerNum) {
		playerThrown = playerNum;
	}

	//set the status of the hat (that if it's being carried by a character)
	void hatOnChar(bool status) {
		onChar = status;
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

private:
	/*when the hat is carried by a character, the hat moves with the character*/
	bool onChar = false;

	/*true if this hat is being rendered */
	bool render = false;

	//the default launch status for this
	glm::vec2 launchStatus;

	// The base damage of the hat.
	const int baseDamage;

	// The damage modifier of the hat.
	const double damageModifier;

	//The fall speed of the hat (when it's airborne).
	const double fallSpeedModifier;

	// The launch velocity of the hat.
	const double launchVelocity;

	// Represents whether or not the hat is thrown by a player.
	// the number is the playernumber
	// 0 means not being thrown
	int playerThrown = 0;
};