#include "InGameObj.h"
class Hat : InGameObj{
public:
	virtual int getHatType() = 0;// pure virtual function providing interface framework.

	Hat();
private:
	int baseDamage;

	double damageModifier;
	
	double fallSpeed;
	
	double launchSpeed;
};