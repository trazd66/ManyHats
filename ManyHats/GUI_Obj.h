#pragma once
#include <iostream>
#include "Texture2D.h"

#include <glm/vec2.hpp>

using std::string;
class GUI_Obj
{
public:
	virtual std::string getGUI_type() = 0;
	// location is the coordinate at button left of the object
	GUI_Obj(glm::vec2 location, double length, double height, Texture2D texture) :
		location(location), length(length), height(height), texture(texture) {
	}

	glm::vec2 getLocation() {//get the location of the object
		return location;
	}

	double getLength() {// get the length of this obj
		return length;
	}

	double getHeight() {//height of this obj
		return height;
	}

	Texture2D getTexture() {
		return texture;
	}

private:
	glm::vec2 location;
	double length;// length of the gui object
	double height;// height of the gui object
	Texture2D texture; // texture used for this gui object
};

