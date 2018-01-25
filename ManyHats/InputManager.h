#pragma once

#include "GameState.h"
#include "GameStateManager.h"

enum inputState {
	ESCAPE_PRESSED,
	DUO_PLAYER_MODE,
	SINGLE_PLAYER_MODE,
	INIT_STATE
};


class InputManager
{
public:
	// Initiate the inputManager with a gamestate.
	static void loadCurrGameState(GameState* gameState);

	// Return the current cursor location with top left corner as (0,0).
	static double* getCursorLocation(GLFWwindow * window);

	// Returns true if the cursor is currently on the given buttons.
	static bool cursorOnButton(GLFWwindow * window, GUI_Button* button);

	// Process keyboard inputs of two players.
	static void process_DUO_gameplay_input(GameStateManager* gsm, GLFWwindow *window);

	// Sets the cursor callback function.
	static void setCursorCallBack(GLFWwindow* window);

	// Processes left clicks.
	static void process_left_click(GLFWwindow * window);

	// Pauses the game.
	static void checkPauseGame(GameStateManager* gsm, bool escKeyDown);

private:

	// The current GameState.
	static GameState * currGameState;
};

