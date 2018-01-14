#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GameWorld.h"

#include "GUI_Button.h"

#include "GL_Sprite_Renderer.h"

class GameState
{
public:
	GameState(GLFWwindow* window, GL_Sprite_Renderer* renderer, GameWorld world) :
		window(window), renderer(renderer), currWorld(world) {};

	~GameState();

	void addButton(GUI_Button button) {
		buttons.push_back(button);
	}
	
	//render the buttons
	void renderGui();

private:
	GLFWwindow* window;

	GL_Sprite_Renderer* renderer;// the renderer that this game state uses

	GameWorld currWorld;

	vector<GUI_Button> buttons; //list of buttons used by in this gameState
};

