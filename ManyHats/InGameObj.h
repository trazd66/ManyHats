#pragma once
class InGameObj
{
public:
	virtual int getItemType() = 0;// pure virtual function providing interface framework.
	
	InGameObj() :x_Vel(0), y_Vel(0),hitBox(),location(){};//velocities of this object is default to 0, initialize the hitBox
	~InGameObj() {};

private:

	double hitBox[2]; // the hit box of this in game item, 1's element is the x location, second is the y location
	double location[2]; // the center of location of this object
	double x_Vel;//x velocity of the object
	double y_Vel;//y velocity of the object

};

