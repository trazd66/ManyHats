#pragma once
#include "Hat.h"
class BombHat : public Hat {
public:
	double y_launch_offSet = 5.0f;

	BombHat(vec2 hitBox) : Hat(10.0f, 1.5f, -0.5f, 5.0f, hitBox, 5) {
		setPlayerThrown(99);
		this->setAirborneStatus(true);
	}

	~BombHat() {

	}

	virtual void launch() {
		if (this->getFaceRight()) {
			this->setVelocity(getLaunchVelocity(), y_launch_offSet);
		}
		else {
			this->setVelocity(-getLaunchVelocity(), y_launch_offSet);
		}
	}

	string getItemType() {
		return "BombHat";
	}
};

