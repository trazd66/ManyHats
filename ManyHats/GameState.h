#pragma once
#include "GameWorld.h"

#include "GUI_Button.h"

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

	GameWorld* getWorld() {
		return currWorld;
	}

	void initGameState(std::function<void()> func);

private:
	GLFWwindow* window;

	std::function<void()> renderCallBack; // call back used during render call

	GameWorld* currWorld; // a game state may or may not contain a gameworld

	vector<GUI_Button*> buttons; //list of buttons used by in this gameState
};

