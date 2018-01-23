#include "GameState.h"


// Default Destructor.
GameState::~GameState()
{
}

// Calls the renderCallBack function.
void GameState::renderCall()
{
	this->renderCallBack();
}

// Sets the renderCallBack function.
void GameState::initGameState(std::function<void()> func)
{
	this->renderCallBack = func;
}

