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

	void init();

	GameState* getCurrState();

	void update();

private:
	void updateGameWorld();

	void switchState(state nextState);

	void setWelcomeState();

	void setgameplayState();

	void setPausedState();

	state currState;

	vector<GameState*> gameStates;

	GL_Manager* manager;

	GL_Sprite_Renderer* renderer;

	GLFWwindow * window;//there really should just be one window
};

