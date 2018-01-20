#pragma once
#include "GUI_Obj.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <functional>

class GUI_Button : public GUI_Obj
{
public:
	GUI_Button(std::function<void()> windowCallBack,
		GLFWwindow * window,
		glm::vec2 location,
		double length,
		double height,
		Texture2D texture)

		:window(window),GUI_Obj(location,length,height,texture) {
		this->windowCallBack = windowCallBack;
	};

	~GUI_Button();

	//type of this gui obj
	string getGUI_type() {
		return "Button";
	}

	void onPressed() {// when the button is pressed down, execute windowCallBack
		this->windowCallBack(); // executes the function
	}

private:
	GLFWwindow* window; // the window where this button belongs to

	std::function<void()>	windowCallBack; // the function that this button is going to execute when pressed

};

