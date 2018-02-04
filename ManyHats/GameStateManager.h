#pragma once
#include "GameState.h"
#include "GL_Sprite_Renderer.h"
#include "Animation.h"

// An enum containing the states of this game.
enum state
{
	Welcome,
	Gameplay,
	Paused
};

// This class deals with the GameStates of this game.
class GameStateManager
{
public:

	// The default constructor.
	GameStateManager(GL_Manager* manager, GL_Sprite_Renderer* renderer);

	// The default destructor.
	~GameStateManager() {};

	// Initializes the states in this GameStateManager, and sets the current state to Welcome.
	void init();

	// Returns the current state of the game.
	GameState* getCurrState();

	/* Updates the game (by calling GameWorld.update()).
	 * Ensures that this updating occurs periodically.
	 */
	void update();

	// Returns the Animation associated to the specified name.
	Animation* getAnim(std::string name) {
		return animMap[name];
	}

	// Sets the game's state to paused.
	void pauseGame() {
		switchState(Paused);
	}

	// Sets the game's state to unpaused.
	void unpauseGame() {
		if (!currState == Welcome) {
			switchState(Gameplay);
		}
	}

	// Sets the game to be paused or to continue.
	void setPaused(bool newValue) {
		gameIsPaused = newValue;
	}

	// Returns whether the game is meant to be paused.
	bool getPaused() {
		return gameIsPaused;
	}

	// Sets the variable representing whether or not the game is ready to be paused.
	void setReadyToBePaused(bool newValue) {
		readyToBePaused = newValue;
	}

	// Returns whether the game is ready to be paused.
	bool getReadyToBePaused() {
		return readyToBePaused;
	}

private:
	//used to initialize walking animation
	void initWalkingAnim();

	void initHatSprite();

	// The game's timer.
	Timer* gameUpdateTimer = new Timer((double)1 / 60);

	// Updates the game world.
	void updateGameWorld();

	// Changes the Game's state.
	void switchState(state nextState);

	// Sets the Welcome state.
	void setWelcomeState();
	void setWelcomeState(GameWorld* world);

	// Sets the GamePlay state.
	void setgameplayState();

	// Sets the Paused state.
	void setPausedState();

	// Adds an animation to the animations map.
	void addAnimToMap(std::string name, Animation* animation);

	// A map from strings to Animation pointers.
	std::map<std::string, Animation*> animMap;

	// The current state of the game, which is a member of the state enum.
	state currState;

	// A vector containing the states of this game.
	vector<GameState*> gameStates;

	// The game's GL Manager.
	GL_Manager* manager;

	// The sprite renderer of the game.
	GL_Sprite_Renderer* renderer;

	// The game's window,which should be unique.
	GLFWwindow * window;

	// The current GameWorld.
	GameWorld* game;

	/* Represents whether the game is ready to be paused
	* (i.e. whether the escape key has been released).
	*/
	bool readyToBePaused = true;

	// True iff game is meant to be paused.  False by default.
	bool gameIsPaused = false;
};
