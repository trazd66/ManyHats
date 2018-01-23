#include "GameStateManager.h"


void GameStateManager::renderGUI_Objs(vector<GUI_Obj*> objs)
{
	for (auto obj : objs) {
		renderer->renderSprite(obj->getTexture(), manager->getShader("Text_Shader"), obj->getLocation());
	}
}

GameStateManager::GameStateManager(GL_Manager * manager, GL_Sprite_Renderer* renderer)
{
	this->manager = manager;
	this->renderer = renderer;
}

GameState* GameStateManager::getCurrState()
{
	return gameStates.at(currState);
}

void GameStateManager::setWelcomeState()
{
	this->currState = Welcome;
	GameState * welcome = new GameState(window);
	this->gameStates.push_back(welcome);


	std::function<void()> windowCallBack = [this]() {
		// the function that this button is going to execute when pressed
		this->switchState(Gameplay);
	};
	//creates a new button
	GUI_Button* startGame = new GUI_Button(
		windowCallBack,
		window,
		glm::vec2(400, 300),
		100, 50,
		manager->getTexture("Button_Texture"));

	welcome->addButton(startGame);


	std::function<void()> renderCall = [this, welcome]() {
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Rendering the background.
		renderer->renderSprite(
			manager->getTexture("BG_Texture"),
			manager->getShader("Char_Shader"),
			glm::vec2(400, 300));

		for (auto button : welcome->getButtons()) {
			renderer->renderSprite(button->getTexture(), manager->getShader("Char_Shader"), button->getLocation(), 0.45f, 0.1f);
		}

		renderer->renderText(
			manager->getShader("Text_Shader"),
			"START GAME!",
			glm::vec2(235, 285),
			glm::vec3(1, 0.5, 0));

	};

	welcome->initGameState(renderCall);

}

void GameStateManager::setgameplayState()
{
	this->currState = Gameplay;
	GameState * gameplay = new GameState(window);
	this->gameStates.push_back(gameplay);

	std::function<void()> renderCall = [this, gameplay]() {
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Rendering the background.
		renderer->renderSprite(
			manager->getTexture("BG_Texture"),
			manager->getShader("Char_Shader"),
			glm::vec2(400, 300));


		// Rendering the platforms.
		for (int i = 0; i < gameplay->getWorld()->getPlatforms().size(); i++) {
			renderer->renderSprite(
				manager->getTexture("Platform_Texture"),
				manager->getShader("Char_Shader"),
				glm::vec2(
				(float)(gameplay->getWorld()->getPlatforms()[i]->getLocation()[0]),
					(float)(gameplay->getWorld()->getPlatforms()[i]->getLocation()[1])),
				0.98f,
				0.04f);
		}

		// Rendering the characters.
		for (int i = 0; i < gameplay->getWorld()->getCharacters().size(); i++) {
			renderer->renderSprite(
				manager->getTexture("Char_Texture" + std::to_string(i)),
				manager->getShader("Char_Shader"),
				glm::vec2(
				(float)(gameplay->getWorld()->getCharacters()[i]->getLocation()[0]),
					(float)(gameplay->getWorld()->getCharacters()[i]->getLocation()[1])),
				0.1f,
				0.1f);
		}

	};

	gameplay->initGameState(renderCall);



}

void GameStateManager::update()
{
}
