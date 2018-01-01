#include"InGameObj.h"
class Character :InGameObj{

private:
	int health = 100;//health of this character, initially set to 100

	static int jumpSpeed;// how high this character can jump

	static int movementSpeed; //how fast this character can move

	const int playerNum;//player number of this character

	
public:
	Character(const int playerNum, double(&hitBox)[2]);

	string getItemType() {
		return "Character";
	};

	static int getJumpSpeed() {
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

	virtual void throwHat();

	virtual void fetchHat();
};