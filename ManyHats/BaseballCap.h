#pragma once
#include "Hat.h"
class BaseballCap :
	public Hat
{
public:

	double y_launch_offSet = 5.0f;

	BaseballCap(vec2 hitBox) :Hat(10.0f, 1.5f, -0.5f, 10.0f, hitBox,0) {}

	virtual void launch() {
		this->setVelocity(getLaunchVelocity(), y_launch_offSet);
		this->setPlayerThrown(true);
		this->setAirborneStatus(true);
	}

	string getItemType() {
		return "BaseballCap";
	}
};

