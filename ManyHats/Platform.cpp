#include "Platform.h"


// Default constructor for the Platform object.
Platform::Platform(int x, int y, double(&hitBox)[2]) : InGameObj(hitBox)
{
	// Set the position of this Platform object.
	setLocation(x, y);

	// TODO:  Why are we multiplying by two?
	width = hitBox[0];
	length = hitBox[1];
}