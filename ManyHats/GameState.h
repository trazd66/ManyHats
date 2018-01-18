#pragma once
#include "GameWorld.h"

#include "GUI_Button.h"

#include "GL_Sprite_Renderer.h"

class GameState
{
public:
	GameState(GLFWwindow* window, GameWorld* world = nullptr) :
		window(window), currWorld(world) {};

	~GameState();

	void addButton(GUI_Button* button) {
		buttons.push_back(button);
	}
	
	void renderCall();

	//returns the buttons that this game state uses
	vector<GUI_Button*> getButtons() {
		return buttons;
	}


	void initGameState(std::function<void()> func);

	void testCall(GL_Sprite_Renderer* renderer, GL_Manager* manager) {
		renderer->renderSprite(
			manager->getTexture("BG_Texture"),
			manager->getShader("Char_Shader"),
			glm::vec2(400, 300));
	}

private:
	GLFWwindow* window;

	std::function<void()> renderCallBack; // call back used during render call

	GameWorld* currWorld; // a game state may or may not contain a gameworld

	vector<GUI_Button*> buttons; //list of buttons used by in this gameState
};

