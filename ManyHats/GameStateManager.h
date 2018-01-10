#pragma once
#include <GLFW/glfw3.h>
#include "GameWorld.h"


#define INITIAL_STATE 0;
#define BEGINING_STATE 1;
#define GAMEPLAY_STATE 2;

class GameStateManager
{
public:
	GameStateManager();

	~GameStateManager();

	// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
	// ---------------------------------------------------------------------------------------------------------
	void processInput(GameWorld* game, GLFWwindow *window)
	{
		// Pressing the Escape key should close the window.
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}

		/* PLAYER 1 MOVEMENT */
		// Deals with horizontal movement.
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
			game->getCharacters()[0]->moveRight();
		} else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
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
		} else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
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

private:
	//primary gameworld
	GameWorld* gameWorld;
	//the current game state
	int currGameSate;
	
	void displayWelcomeScreen();

	//bind the input based on number of players
	void bindInput(int numOfPlayer);

};

