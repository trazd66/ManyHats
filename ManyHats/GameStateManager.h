#pragma once
#include <glad/glad.h>
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

	void processInput(GLFWwindow *window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
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

