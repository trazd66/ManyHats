#pragma once
#include <glad/glad.h> 

// GLFW
#include <GLFW/glfw3.h>

class Timer
{
public:

	Timer(double fps,bool start = true) :limitFPS(fps) {
		if (start) { this->start(); }
	};
	
	~Timer();

	void start() {
		deltaTime = 0;
		lastTime = glfwGetTime();
		 nowTime = 0;
	}

	void update() {
		// - Measure time
		nowTime = glfwGetTime();
		deltaTime += (nowTime - lastTime)/limitFPS;
		lastTime = nowTime;
	}

	bool ticks() {
		// - Only update at 60 frames / s
		if (deltaTime >= 1.0) {
			deltaTime--;
			return true;
			// - Update function
		}
		return false;
	}

private:
	double deltaTime = 0;
	
	double limitFPS;
	
	double lastTime = glfwGetTime(), timer = lastTime;

	double nowTime = 0;

};

