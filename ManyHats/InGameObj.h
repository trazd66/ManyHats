#pragma once
#include <iostream>
using std::string;

// An abstract class to represent any sprite.
class InGameObj
{
public:
	// Pure virtual function providing interface framework.
	virtual string getItemType() = 0;

	// Velocities of this object are 0 by default, initialize the hitBox.
	InGameObj(double (&arr)[2]) : x_Vel(0), y_Vel(0), location(), hitBox(arr) {

	};

	// Destructor of the object.
	~InGameObj() {
		// delete [] &hitBox;
		// delete [] &location;
		// delete &x_Vel;
		// delete &y_Vel;
	};

	// Returns whether or not the object is floating in the air.
	bool getAirborneStatus() {
		return airborne;
	}

	// Get the location of the object.
	double* getLocation() {
		return location;
	};

	// Get the x velocity of the object.
	int getX_vel() {
		return x_Vel;
	}

	// Get the y velocity of the object.
	int getY_vel() {
		return y_Vel;
	}

	// Set the location of the object.
	void setLocation(const double x, const double y){
		location[0] = x;
		location[1] = y;
	};

	// Set the velocity of the object.
	void setVelocity(const int x, const int y) {
		x_Vel = x;
		y_Vel = y;
	}

	// Set y velocity only.
	void setY_vel(const int y) {
		y_Vel = y;
	}

	// Set x velocity only.
	void setX_vel(const int x) {
		x_Vel = x;
	}

	// Sets the airborne variable.
	void setAirborneStatus(bool status) {
		// True if airborne, false if not airborne.
		airborne = status;
	}

	// Returns the pointer to the hitBox of this object.
	double* getHitBox() {
		return hitBox;
	}

	// Returns whether this InGameObj is touching obj.
	bool touching(InGameObj& obj) {
		// Basically, return true if and only if my left < obj's right and obj's left < my right and my bottom < obj's top and obj's bottom < my top.
		return (location[0] - (hitBox[0] / 2) < obj.location[0] + (obj.hitBox[0] / 2))
		&& (obj.location[0] - (obj.hitBox[0] / 2) < location[0] + (hitBox[0] / 2))
		&& (location[1] - (hitBox[1] / 2) < obj.location[1] + (obj.hitBox[1] / 2))
		&& (obj.location[1] - (obj.hitBox[1] / 2) < location[1] + (hitBox[1] / 2));
	}

	// Update this object.
	void update() {
		location[0] += x_Vel;
		location[1] += y_Vel;
	}

	// Gets the image string of this object.
	string getImage() {
		return image;
	}

	// Sets the image property of this object.
	void setImage(string newImage) {
		image = newImage;
	}

private:

	// The hit box of this in game item, x as first element, y as the second element
	double (&hitBox)[2];

	// The centre of location of this object, x as first element, y as the second element
	double location[2];

	// X velocity of the object.
	int x_Vel;

	// Y velocity of the object.
	int y_Vel;

	// Represents whether or not the object is floating in the air.
	bool airborne = false;

	// The name of the image that the InGameObj should have.
	string image;
};

