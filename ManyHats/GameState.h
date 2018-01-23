#pragma once
#include "GameWorld.h"

#include "GUI_Button.h"

// Represents a state in this game.
class GameState
{
public:

	// Default constructor.
	GameState(GLFWwindow* window, GameWorld* world = nullptr) :
		window(window), currWorld(world) {};

	// Default destructor.
	~GameState();

	// Adds a button to this game.
	void addButton(GUI_Button* button) {
		buttons.push_back(button);
	}
	
	// Calls the renderCallBack function.
	void renderCall();

	// Returns the buttons that this game state uses.
	vector<GUI_Button*> getButtons() {
		return buttons;
	}

	// Returns the GameWorld being used currently.
	GameWorld* getWorld() {
		return currWorld;
	}

	// Initializes the game's state.
	void initGameState(std::function<void()> func);

private:

	// The current game's window.
	GLFWwindow* window;

	// call back used during render call.
	std::function<void()> renderCallBack; 
	
	// A GameState may or may not contain a GameWorld.
	GameWorld* currWorld;

	// List of buttons used by this GameState.
	vector<GUI_Button*> buttons; 
};

