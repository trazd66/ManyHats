#include"InGameObj.h"
class Character :InGameObj{

private:
	int health;
	int playerNum;
public:
	int getHealth();

	Character(int playerNum);
	
	virtual void jump();

	virtual void move();

	virtual void throwHat();

};