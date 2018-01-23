#pragma once
#include "GameState.h"

#include "GL_Sprite_Renderer.h"

enum state
{
	Welcome,
	Gameplay
};


class GameStateManager
{
public:
	GameStateManager(GL_Manager* manager, GL_Sprite_Renderer* renderer);

	~GameStateManager() {};

	void switchState(state nextState) {
		currState = nextState;
		this->update();	
	}


	void init();

	GameState* getCurrState();

	void setWelcomeState();

private:

	

	void setgameplayState();

	void update();

	state currState;
	
	vector<GameState*> gameStates;

	GL_Manager* manager;

	GL_Sprite_Renderer* renderer;

	GLFWwindow * window;//there really should just be one window

	void renderGUI_Objs(vector<GUI_Obj*> objs);
};

