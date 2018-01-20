#pragma once

#include "GameState.h"

enum inputState {
	ESCAPE_PRESSED,
	DUO_PLAYER_MODE,
	SINGLE_PLAYER_MODE,
	INIT_STATE
};


class InputManager
{
public:
	//initiate the inputManager with a gamestate
	static void loadCurrGameState(GameState* gameState);

	//return the current cursor location with top left corner as (0,0)
	static double* getCursorLocation(GLFWwindow * window);

	// true if the cursor is currently on the given buttons
	static bool cursorOnButton(GLFWwindow * window, GUI_Button* button);

	// process keyboard inputs of two players
	static void process_DUO_gameplay_input(GameWorld* game, GLFWwindow *window);

	static void setCursorCallBack(GLFWwindow* window);


	static void process_left_click(GLFWwindow * window);


private:

	static GameState * currGameState;

};

