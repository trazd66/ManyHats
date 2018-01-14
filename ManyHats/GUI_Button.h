#pragma once
#include "GUI_Obj.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <functional>

class GUI_Button : GUI_Obj
{
public:
	GUI_Button(std::function<void(GLFWwindow&)> windowCallBack,
		GLFWwindow * window,
		double location[2],
		double length, 
		double height, 
		Texture2D texture)

		:windowCallBack(windowCallBack),window(window),GUI_Obj(location,length,height,texture) {};

	~GUI_Button();

	//type of this gui obj
	string getGUI_type() {
		return "Button";
	}

private:
	GLFWwindow* window; // the window where this button belongs to

	std::function<void(GLFWwindow&)>	windowCallBack; // the function that this button is going to execute when pressed

	void onPressed() {// when the button is pressed down, execute windowCallBack
		windowCallBack(*window); // executes the function
	}
};

