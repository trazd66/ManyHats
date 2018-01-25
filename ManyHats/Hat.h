#pragma once // Can CDH sort this out?  -Papa Dylan
#include "InGameObj.h"

// Represents a Hat in the game.
class Hat : public InGameObj{
public:
	// The default constructor for this class.
	Hat(const int baseDamage, const double damageModifier, const double fallSpeed, const double launchSpeed, double (&hitBox)[2])
		: baseDamage(baseDamage), damageModifier(damageModifier), fallSpeedModifier(fallSpeed), launchVelocity(launchSpeed), InGameObj(hitBox)
	{

	};

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

	// Returns true if the hat is being thrown by a player, false otherwise.
	bool getThrownStatus() {
		return playerThrown;
	}

	// True if the hat is thrown by a player, false otherwise.
	void setPlayerThrown(bool status) {
		playerThrown = status;
	}

	virtual void launch() = 0;

private:
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
	bool playerThrown = false;
};