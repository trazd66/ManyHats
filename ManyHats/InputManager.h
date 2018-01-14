#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

enum inputState {
	ESCAPE_PRESSED,
	DUO_PLAYER_MODE,
	SINGLE_PLAYER_MODE,
	INIT_STATE
};

class InputManager
{
public:

	//return the current cursor location with top left corner as (0,0)
	static double* getCursorLocation(GLFWwindow * window) {
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		double location[2] = { xpos,ypos };
		return location;
	}


	static void processKeyboardInput(GLFWwindow * window, inputState) {

	}

private:
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
			//if is pressed inside a button
		}

	}
};

