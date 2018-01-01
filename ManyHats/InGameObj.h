#pragma once
using std::string;
class InGameObj
{
public:
	virtual string getItemType() = 0;// pure virtual function providing interface framework.

	InGameObj(double (&arr)[2]) :x_Vel(0), y_Vel(0),location(),hitBox(arr){
	};//velocities of this object is default to 0, initialize the hitBox

	~InGameObj() {//destructor of the object
		delete [] hitBox;
		hitBox = NULL;

		delete [] location;
		location = NULL;

		delete &x_Vel;
		delete &y_Vel;
	};

	bool getAirborneStatus() {
		return airborne;
	}

	double* getLocation() {// get the location of the object
		return location;
	};

	double getX_vel() {// get the x velocity of the object
		return x_Vel;
	}

	double getY_vel() {// get the y velocity of the object
		return y_Vel;
	}

	void setLocation(const double x,const double y){// set the location of the object
		location[0] = x;
		location[1] = y;
	};

	void setVelocity(const double x, const double y) {// set the velocity of the object
		x_Vel = x;
		y_Vel = y;
	}

	void setY_vel(const double y) {// set y velocity only
		y_Vel = y;
	}

	void setX_vel(const double x) {// set x velocity only
		x_Vel = x;
	}

	void setAirborneStatus(bool status) {
		airborne = status;
	}

private:

	double (&hitBox)[2]; // the hit box of this in game item, x as first element, y as the second element
	double location[2]; // the center of location of this object,x as first element, y as the second element
	double x_Vel;//x velocity of the object
	double y_Vel;//y velocity of the object
	bool airborne = false;
};

