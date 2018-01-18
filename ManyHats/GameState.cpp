#include "GameState.h"





GameState::~GameState()
{
}


void GameState::renderCall()
{
	this->renderCallBack();
}

void GameState::initGameState(std::function<void()> func)
{
	this->renderCallBack = func;
}

