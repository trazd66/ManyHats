#include"InGameObj.h"
class Character :InGameObj{

private:
	int health = 100;//health of this character, initially set to 100

	const int playerNum;//player number of this character

public:
	Character(const int playerNum, double(&arr)[2]);

	int Character::getHealth()//returns the health of this character
	{
		return this->health;
	}

	void setHealth(int num);//set the health of this character

	
	virtual void jump();

	virtual void moveLeft();

	virtual void moveRight();

	virtual void throwHat();

};