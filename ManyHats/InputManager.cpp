#include "InputManager.h"


GameState* InputManager::currGameState;

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
		InputManager::currGameState = gameState;
	}
	else {
		//gameState = nullptr;
	}
}

double * InputManager::getCursorLocation(GLFWwindow * window)
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	double location[2] = { xpos, abs( ypos-600)}; //position with top left corner as (0,0)
	return location;
}

bool InputManager::cursorOnButton(GLFWwindow * window, GUI_Button * button)
{
	double x_loc = button->getLocation().x;//x location of the button
	double y_loc = button->getLocation().y;//y location of the button

	double y_diff0 = y_loc - button->getHeight() / 2;
	double y_diff1 = y_loc + button->getHeight() / 2;
	double x_diff0 = x_loc - button->getLength() / 2;
	double x_diff1 = x_loc + button->getLength() / 2;
	if ((y_diff0 <= getCursorLocation(window)[1] && getCursorLocation(window)[1] <= y_diff1) &&
		(x_diff0 <= getCursorLocation(window)[0] && getCursorLocation(window)[0] <= x_diff1)) {
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
		game->getCharacters()[0]->standStill();
	}

	// Deals with vertical movement.
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && !(game->getCharacters()[0]->getAirborneStatus())) {
		game->getCharacters()[0]->jump();
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
		game->getCharacters()[1]->standStill();
	}

	// Deals with vertical movement.
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && !(game->getCharacters()[1]->getAirborneStatus())) {
		game->getCharacters()[1]->jump();
	}
}

void InputManager::setCursorCallBack(GLFWwindow * window)
{
	glfwSetMouseButtonCallback(window, mouse_button_callback);//bind call back function
}

void InputManager::process_left_click(GLFWwindow * window)
{
	for (auto button : currGameState->getButtons()) {
		if (InputManager::cursorOnButton(window, button)) {
			button->onPressed();
			return;
		}
	}
}


