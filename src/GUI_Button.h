#pragma once
#include "GUI_Obj.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <functional>

class GUI_Button : public GUI_Obj
{
public:

	// Default constructor.
	GUI_Button(
		std::function<void()> windowCallBack,
		GLFWwindow * window,
		glm::vec2 location,
		double length,
		double height,
		Texture2D texture
	) : window(window),GUI_Obj(location,length,height,texture) 
	{
		this->windowCallBack = windowCallBack;
	};

	// Default destructor.
	~GUI_Button();

	// Returns the type of this GUI object.
	string getGUI_type() {
		return "Button";
	}
	
	// When the button is pressed down, execute windowCallBack().
	void onPressed() {
		// Executes the function.
		this->windowCallBack(); 
	}

private:
	// The window that this button belongs to.
	GLFWwindow* window; 

	// The function that this button is going to execute when pressed.
	std::function<void()>	windowCallBack; 

};

