#pragma once
#include "InGameObj.h"
class Platform :
	// if a character is not airborne, then it must be on a platform
	//platforms are rectangles basically
	public InGameObj
{

private:
	double width;
	double length;

public:
	string getItemType() {
		return "Platform";
	}

	Platform(double(&hitBox)[2]);

	~Platform() {
		delete &width;
		delete &length;
	};
};

