#pragma once
#include "Hat.h"
class ChiefHat :
	public Hat
{
public:

	double y_launch_offSet = 5.0f;

	ChiefHat(vec2 hitBox) :Hat(-10.0f, 1.5f, -0.5f, 5.0f, hitBox, 4) {}

	virtual void launch() {
		if (this->getFaceRight()) {
			this->setVelocity(getLaunchVelocity(), y_launch_offSet);
		}
		else {
			this->setVelocity(-getLaunchVelocity(), y_launch_offSet);
		}
		this->setPlayerThrown(true);
		this->setAirborneStatus(true);
	}

	string getItemType() {
		return "ChiefHat";
	}
};

