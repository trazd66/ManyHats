#include "Platform.h"


// Default constructor for the Platform object.
Platform::Platform(int x, int y, double(&hitBox)[2]) : InGameObj(hitBox)
{
	// Set the position of this Platform object.
	getLocation()[0] = x;
	getLocation()[1] = y;

	// TODO:  Why are we multiplying by two?
	width = hitBox[0] * 2;
	length = hitBox[1] * 2;
}

