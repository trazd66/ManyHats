#pragma once
#include "InGameObj.h"

// If a character is not airborne, then it must be on a platform.
class Platform : public InGameObj
{

private:
	// The width of this platform.
	double width;

	// The height of this platform.
	double length;

public:

	// Returns the type of this object.
	std::string getItemType() {
		return "Platform";
	}

	// Default constructor for this class.
	Platform(int x, int y, double(&hitBox)[2]) 
		: width(x), length(y), InGameObj(hitBox) 
	{
	};

	// Default destructor for this class.
	~Platform() {
		delete &width;
		delete &length;
	};
};

