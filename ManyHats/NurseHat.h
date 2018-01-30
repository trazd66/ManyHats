#pragma once
#include "Hat.h"
class NurseHat :
	public Hat
{
public:

	double y_launch_offSet = 0.0f;

	NurseHat(vec2 hitBox) :Hat(-10.0f, 1.5f, -0.5f, 5.0f, hitBox, 1) {
		reset();
	}

	virtual void launch() {
		//cannot launch this hat
	}

	virtual void reset() {
		this->setAirborneStatus(true);
		this->setPlayerThrown(99);
		this->setRenderStatus(false); // should no longer be rendered

	}

	string getItemType() {
		return "NurseHat";
	}
};

