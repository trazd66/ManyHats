#include "InGameObj.h"
class Hat : InGameObj{
public:
	Hat(const int baseDamage,const double damageModifier,const double fallSpeed,const double launchSpeed,double (&hitBox)[2])
		:baseDamage(baseDamage),damageModifier(damageModifier),fallSpeedModifier(fallSpeed), launchVelocity(launchSpeed), InGameObj(hitBox)
	{};

	~Hat() {
		delete & baseDamage;
		delete & damageModifier;
		delete & fallSpeedModifier;
		delete & launchVelocity;
		delete & playerThrown;
	};

	int getBaseDamage() {//returns the baseDamage of the hat
		return this->baseDamage;
	};

	double getDamageModifier() {//returns the damage modifier of the hat
		return this->damageModifier;
	};

	double getFallSpeed() {// returns the fallspead of the hat
		return this->fallSpeedModifier;
	};

	double getLaunchVelocity() {// returns the launch velocity of the hat
		return this->launchVelocity;
	};

	virtual void launch(double xDir,double yDir) = 0;// launches the hat with given direction!

	bool getThrownStatus() {
		return playerThrown;
	}

	void setPlayerThrown(bool status) {
		playerThrown = status;
	}
	
private:
	const int baseDamage;//the base damage of the hat

	const double damageModifier;// damage modifier of the hat
	
	const double fallSpeedModifier;//fall speed of the hat (when it's airborne)
	
	const double launchVelocity;//launch velocity of the hat

	bool playerThrown = false;
};