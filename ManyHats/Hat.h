#include "InGameObj.h"
class Hat : InGameObj{
public:
	virtual int getHatType() = 0;// pure virtual function providing interface framework.

	Hat(int BaseDamage, double damageModifier, double fallSpeed, double launchSpeed){
		this->baseDamage = BaseDamage;
		this->damageModifier = damageModifier;
		this->fallSpeed = fallSpeed;
		this->launchVelocity = launchSpeed;
	};

	int getBaseDamage() {
		return this->baseDamage;
	};

	double getDamageModifier() {
		return this->damageModifier;
	};

	double getFallSpeed() {
		return this->fallSpeed;
	};

	double getLaunchVelocity() {
		return this->launchVelocity;
	};

	
private:
	int baseDamage;

	double damageModifier;
	
	double fallSpeed;
	
	double launchVelocity;
};