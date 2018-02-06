#pragma once
#include "Hat.h"
class SantaHat :
	public Hat
{
public:
	double y_launch_offSet = 30.0f;

	SantaHat(vec2 hitBox) : Hat(10.0f, 1.5f, -0.5f, 5.0f, hitBox, 2) {}

	virtual void launch() {
		if (this->getFaceRight()) {
			this->setVelocity(getLaunchVelocity()/5, y_launch_offSet);
		}
		else {
			this->setVelocity(-getLaunchVelocity()/5, y_launch_offSet);
		}
	}

	virtual void reset() {
		this->setPlayerThrown(0);
		this->setAirborneStatus(true);//unless carried by a character, the hat will always fall
		this->setCharNum(0);
		this->setRenderStatus(false);
		this->setVelocity(0, 0);
		this->setLocation(900, 900);
		this->setGoDownFaster(false);
	}

	string getItemType() {
		return "SantaHat";
	}
};

