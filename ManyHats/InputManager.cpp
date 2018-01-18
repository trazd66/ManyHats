#include "InputManager.h"



void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		InputManager::process_left_click(window);
	}
}



void InputManager::loadCurrGameState(GameState * gameState)
{
	if (gameState != nullptr) {
		//InputManager::currGameState = gameState;
	}
	else {
		//gameState = nullptr;
	}
}

double * InputManager::getCursorLocation(GLFWwindow * window)
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	double location[2] = { xpos,ypos };
	return location;
}

bool InputManager::cursorOnButton(GLFWwindow * window, GUI_Button * button)
{
	double x_loc = button->getLocation()[0];// bottom left x location of the button
	double y_loc = button->getLocation()[1];// bottom left y location of the button

	if (y_loc <= getCursorLocation(window)[0] <= y_loc + button->getHeight() &&
		x_loc <= getCursorLocation(window)[1] <= x_loc + button->getLength()
		) {
		return true;
	}
	return false;
}

void InputManager::process_DUO_gameplay_input(GameWorld * game, GLFWwindow * window)
{
	// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
	// Pressing the Escape key should close the window.
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		//	glfwSetWindowShouldClose(window, true);
	}

	/* PLAYER 1 MOVEMENT */
	// Deals with horizontal movement.
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		game->getCharacters()[0]->moveRight();
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		game->getCharacters()[0]->moveLeft();
	}
	else {
		game->getCharacters()[0]->setX_vel(0);
	}

	// Deals with vertical movement.
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && !(game->getCharacters()[0]->getAirborneStatus())) {
		game->getCharacters()[0]->setAirborneStatus(true);
		game->getCharacters()[0]->setY_vel(game->getCharacters()[0]->getJumpSpeed());
	}


	/* PLAYER 2 MOVEMENT */
	// Deals with horizontal movement.
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		game->getCharacters()[1]->moveRight();
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		game->getCharacters()[1]->moveLeft();
	}
	else {
		game->getCharacters()[1]->setX_vel(0);
	}

	// Deals with vertical movement.
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && !(game->getCharacters()[1]->getAirborneStatus())) {
		game->getCharacters()[1]->setAirborneStatus(true);
		game->getCharacters()[1]->setY_vel(game->getCharacters()[1]->getJumpSpeed());
	}
}

void InputManager::setCursorCallBack(GLFWwindow * window)
{
	glfwSetMouseButtonCallback(window, mouse_button_callback);//bind call back function
}

void InputManager::process_left_click(GLFWwindow * window)
{
	//for (auto button : currGameState->getButtons()) {
		//if (InputManager::cursorOnButton(window, button)) {
			//button->onPressed();
			//return;
		//}
//	}
}


