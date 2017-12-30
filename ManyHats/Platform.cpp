#include "Platform.h"


Platform::Platform(double(&hitBox)[2]): InGameObj(hitBox)
{
	width = hitBox[0] * 2;
	length = hitBox[1] * 2;
}

