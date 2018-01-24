#pragma once
#include "GameState.h"

#include "GL_Sprite_Renderer.h"
#include "Animation.h"

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

	Animation* getAnim(std::string name) {
		return animMap[name];
	}

private:
	Timer* gameUpdateTimer = new Timer((double)1 / 60);

	void updateAnimation();

	void updateGameWorld();

	void switchState(state nextState);

	void setWelcomeState();

	void setgameplayState();

	void setPausedState();

	void addAnimToMap(std::string name,Animation* animation);

	std::map<std::string,Animation*> animMap;

	state currState;

	vector<GameState*> gameStates;

	GL_Manager* manager;

	GL_Sprite_Renderer* renderer;

	GLFWwindow * window;//there really should just be one window
};
