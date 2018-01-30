#pragma once
#include <iostream>
#include "Texture2D.h"

#include <glm/vec2.hpp>

using std::string;

class GUI_Obj
{
public:

	// Returns the type of this GUI.  This is a virtual method.
	virtual std::string getGUI_type() = 0;

	// Location is the coordinate at bottom left of the object.
	GUI_Obj(glm::vec2 location, double length, double height, Texture2D texture) :
		location(location), length(length), height(height), texture(texture) {
	}

	// Get the location of this object.
	glm::vec2 getLocation() {
		return location;
	}

	// Get the length of this object.
	double getLength() {
		return length;
	}

	// The height of this object.
	double getHeight() {
		return height;
	}

	// Returns the texture of this object.
	Texture2D getTexture() {
		return texture;
	}

private:
	
	// The location of this object.
	glm::vec2 location;

	// The length of the GUI object.
	double length;

	// The height of the GUI object.
	double height;

	// The texture used for this GUI object.
	Texture2D texture;
};

