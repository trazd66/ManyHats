#pragma once
#include "Hat.h"
class BaseballCap :
	public Hat
{
public:

	double y_launch_offSet = 5.0f;

	BaseballCap(vec2 hitBox) :Hat(25.0f, 1.5f, -0.5f, 5.0f, hitBox, 5) {
		reset();
	}

	virtual void launch() {
		if (this->getFaceRight()) {
			this->setVelocity(getLaunchVelocity(), y_launch_offSet);
		}
		else {
			this->setVelocity(-getLaunchVelocity(), y_launch_offSet);
		}
	}

	virtual void reset() {
		this->setPlayerThrown(0);
		this->setAirborneStatus(true);//unless carried by a character, the hat will always fall
		this->setCharNum(0);
		this->setRenderStatus(false);
		this->setVelocity(0,0);
		this->setLocation(900, 900);
	}

	string getItemType() {
		return "BaseballCap";
	}
};