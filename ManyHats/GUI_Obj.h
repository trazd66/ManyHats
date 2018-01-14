#pragma once
#include <iostream>
#include "Texture2D.h"

using std::string;
class GUI_Obj
{
public:
	virtual std::string getGUI_type() = 0;
	GUI_Obj(double loc[2], double height, double length, Texture2D texture) : height(height), length(length), texture(texture) {
		location[0] = loc[0];
		location[1] = loc[1];
	}

private:
	double location[2];	// The centre of location of this object, x as first element, y as the second element
	double length;// length of the gui object
	double height;// height of the gui object
	Texture2D texture; // texture used for this gui object
};

