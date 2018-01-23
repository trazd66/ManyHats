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
	double limitFPS = 1.0 / 60.0;

	double lastTime = glfwGetTime(), timer = lastTime;
	double deltaTime = 0, nowTime = 0;
	int frames = 0, updates = 0;


	void updateGameWorld();

	void switchState(state nextState);

	void setWelcomeState();

	void setgameplayState();

	void setPausedState();

	void addAnimToMap(std::string name, Animation* animation);

	// A map from strings to Animation pointers.
	std::map<std::string, Animation*> animMap;

	state currState;

	vector<GameState*> gameStates;

	GL_Manager* manager;

	GL_Sprite_Renderer* renderer;

	GLFWwindow * window;//there really should just be one window
};