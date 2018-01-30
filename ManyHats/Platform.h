#pragma once
#include "InGameObj.h"

// If a character is not airborne, then it must be on a platform.
class Platform : public InGameObj
{


public:

	// Returns the type of this object.
	std::string getItemType() {
		return "Platform";
	}

	// Default constructor for this class.
	Platform(int x, int y, vec2 hitBox) 
		: InGameObj(hitBox) 
	{
		setLocation(x, y);
	};


};

