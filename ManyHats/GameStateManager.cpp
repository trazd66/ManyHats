#include "GameStateManager.h"



GameStateManager::GameStateManager(GL_Manager * manager, GL_Sprite_Renderer* renderer)
{
	this->manager = manager;
	this->renderer = renderer;
}

void GameStateManager::switchState(state nextState)
{
	this->currState = nextState;
}

void GameStateManager::init()
{
	setWelcomeState();
	setgameplayState();
	setPausedState();
	this->currState = Welcome;
}

GameState* GameStateManager::getCurrState()
{
	return gameStates.at(currState);
}

void GameStateManager::setWelcomeState()
{
	GameState * welcome = new GameState(window);
	this->gameStates.push_back(welcome);

	std::function<void()> windowCallBack = [this]() mutable {
		// the function that this button is going to execute when pressed
		this->switchState(Gameplay);
	};

	//creates a new button
	GUI_Button* startGame = new GUI_Button(
		windowCallBack,
		window,
		glm::vec2(400, 300),
		320, 60,
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
			renderer->renderSprite(button->getTexture(), manager->getShader("Char_Shader"), button->getLocation(), 0.4f, 0.1f);
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
	GameWorld* game = new GameWorld();
	GameState * gameplay = new GameState(window, game);
	this->gameStates.push_back(gameplay);

	game->initiate();
	Animation* moveLeft = new Animation(renderer,
		manager->getTexture("char_sprite_text"),
		manager->getShader("char_sprite"),
		glm::vec2(0.120, 0.5),
		glm::vec2(0.120, 0.5),
		7);

	Animation* moveRight = new Animation(renderer,
		manager->getTexture("char_sprite_text"),
		manager->getShader("char_sprite"),
		glm::vec2(0.120, 0.5),
		glm::vec2(0.120, 0),
		7);

	this->addAnimToMap("moveLeft", moveLeft);
	this->addAnimToMap("moveRight", moveRight);

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
			getAnim("moveLeft")->render(gameplay->getWorld()->getCharacters()[i]);
		}

	};

	gameplay->initGameState(renderCall);
}

void GameStateManager::setPausedState()
{

}

void GameStateManager::addAnimToMap(std::string name, Animation* animation)
{
	animMap[name] = animation;
}

void GameStateManager::update()
{
	// - Measure time
	nowTime = glfwGetTime();
	deltaTime += (nowTime - lastTime) / limitFPS;
	lastTime = nowTime;

	// - Only update at 60 frames / s
	while (deltaTime >= 1.0) {
		this->updateGameWorld();
		// - Update function
		updates++;
		deltaTime--;
	}
}

void GameStateManager::updateGameWorld()
{
	if (getCurrState()->getWorld() != nullptr) {
		this->getCurrState()->getWorld()->update();
	}
}