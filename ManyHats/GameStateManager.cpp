#include "GameStateManager.h"


// Default constructor.
GameStateManager::GameStateManager(GL_Manager * manager, GL_Sprite_Renderer* renderer)
{
	this->manager = manager;
	this->renderer = renderer;
}

// Changes the current GameState.
void GameStateManager::switchState(state nextState)
{
	this->currState = nextState;
}

// Initializes the states in this GameStateManager, and sets the current state to Welcome.
void GameStateManager::init()
{
	setWelcomeState();
	setgameplayState();
	setPausedState();
	this->currState = Welcome;
}

// Returns the current GameState.
GameState* GameStateManager::getCurrState()
{
	return gameStates.at(currState);
}

void GameStateManager::setWelcomeState(GameWorld* world) {
	game = world;
	// setWelcomeState();
}

// Sets the Welcome GameState.
void GameStateManager::setWelcomeState()
{
	GameState * welcome = new GameState(window);
	this->gameStates.push_back(welcome);

	std::function<void()> windowCallBack = [this]() mutable {
		// The function that this button is going to execute when pressed.
		this->switchState(Gameplay);
	};

	// Creates a new button.
	GUI_Button* startGame = new GUI_Button(
		windowCallBack,
		window,
		glm::vec2(400, 300),
		320, 60,
		manager->getTexture("Button_Texture")
	);

	// Adds a button to start the game.
	welcome->addButton(startGame);

	std::function<void()> renderCall = [this, welcome]() {
		// Clear the colour buffer.
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Rendering the background.
		renderer->renderSprite(
			manager->getTexture("init_BG_Texture"),
			manager->getShader("Char_Shader"),
			glm::vec2(400, 300)
		);

		for (auto button : welcome->getButtons()) {
			renderer->renderSprite(button->getTexture(), 
				manager->getShader("Char_Shader"), 
				button->getLocation(), 
				0.4f, 
				0.4f
			);
		}

		renderer->renderText(
			manager->getShader("Text_Shader"),
			"The Hat Game During Lecture",
			glm::vec2(100, 500),
			glm::vec3(1, 0.5, 0),
			0.8
		);
	};

	welcome->initGameState(renderCall);
}

// Sets the GamePlay GameState.
void GameStateManager::setgameplayState()
{
	GameWorld* game = new GameWorld();

	// This is required, so that the Paused state can use the game object.
	this->game = game;
	GameState* gameplay = new GameState(window, game);
	this->gameStates.push_back(gameplay);

	game->initiate();

	this->initWalkingAnim();
	
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
		for (auto platform: gameplay->getWorld()->getPlatforms()) {
			renderer->renderSprite(
				manager->getTexture("Platform_Texture"),
				manager->getShader("Char_Shader"),
				glm::vec2(
				(float)(platform->getLocation()[0]),
				(float)(platform->getLocation()[1] - 26)),
				platform->getHitBox().x / 800,
				platform->getHitBox().y / 600);
		}

		// render the hats
		for (auto hat : gameplay->getWorld()->getHats()) {
			if (hat->getRenderStatus()) {
				renderer->renderSprite(
					manager->getTexture("Platform_Texture"),
					manager->getShader("Char_Shader"),
					glm::vec2(
					(float)(hat->getLocation()[0]),
						(float)(hat->getLocation()[1])),
					0.98f,
					0.04f
				);
			}
		}

		// Rendering the characters.
		// Called in the render loop
		for (int i = 0; i < gameplay->getWorld()->getCharacters().size(); i++) {
			string charName_left = "char" + std::to_string(i) + "moveLeft";
			string charName_right = "char" + std::to_string(i) + "moveRight";
			if (gameplay->getWorld()->getCharacters()[i]->ifFaceRight()) {
				//if (gameplay->getWorld()->getCharacters()[i]){
					//add the throw hat move
				//} else
				if (gameplay->getWorld()->getCharacters()[i]->getAirborneStatus()) {//jumping
					getAnim(charName_right)->staticRender(gameplay->getWorld()->getCharacters()[i], 5);
				}
				else if (gameplay->getWorld()->getCharacters()[i]->currMoving()) {
					getAnim(charName_right)->render(gameplay->getWorld()->getCharacters()[i]);//moving
				}
				else {
					getAnim(charName_right)->staticRender(gameplay->getWorld()->getCharacters()[i], 0);
				}
			}
			else {//facing left
				if (gameplay->getWorld()->getCharacters()[i]->getAirborneStatus()) {//jumping
					getAnim(charName_left)->staticRender(gameplay->getWorld()->getCharacters()[i], 5);
				} else if (gameplay->getWorld()->getCharacters()[i]->currMoving()) {
					getAnim(charName_left)->render(gameplay->getWorld()->getCharacters()[i]);//moving
				} else {//standing still
					getAnim(charName_left)->staticRender(gameplay->getWorld()->getCharacters()[i], 0);
				}
			}
		}

		// Render player faces.
		renderer->renderSprite(
			manager->getTexture("head0"),
			manager->getShader("Char_Shader"),
			glm::vec2(
				80,
				90),
			0.05f,
			0.05f
		);

		renderer->renderSprite(
			manager->getTexture("head1"),
			manager->getShader("Char_Shader"),
			glm::vec2(
				720,
				90),
			0.05f,
			0.05f
		);

		// Render player health.
		renderer->renderText(
			manager->getShader("Text_Shader"),
			"HP:  " + std::to_string(this->getCurrState()->getWorld()->getCharacters()[1]->getHealth()),
			glm::vec2(640, 0),
			glm::vec3(1, 0.5, 0),
			0.8
		);

		renderer->renderText(
			manager->getShader("Text_Shader"),
			"HP:  " + std::to_string(this->getCurrState()->getWorld()->getCharacters()[0]->getHealth()),
			glm::vec2(0, 0),
			glm::vec3(1, 0.5, 0),
			0.8
		);
		
		// Render player lives.
		renderer->renderText(
			manager->getShader("Text_Shader"),
			"Lives:  " + std::to_string(this->getCurrState()->getWorld()->getCharacters()[1]->getLives()),
			glm::vec2(640, 45),
			glm::vec3(1, 0.5, 0),
			0.8
		);

		renderer->renderText(
			manager->getShader("Text_Shader"),
			"Lives:  " + std::to_string(this->getCurrState()->getWorld()->getCharacters()[0]->getLives()),
			glm::vec2(0, 45),
			glm::vec3(1, 0.5, 0),
			0.8
		);
	};
	gameplay->initGameState(renderCall);
}

// Sets the paused state of this game.
void GameStateManager::setPausedState()
{
	GameState * paused = new GameState(window, this->game);
	this->gameStates.push_back(paused);

	std::function<void()> renderCall = [this, paused]() {
		// TODO:  Do we need anything else to happen in here?
		renderer->renderText(
			manager->getShader("Text_Shader"),
			"PAUSED",
			glm::vec2(235, 285),
			glm::vec3(1, 0.5, 0));
	};
	paused->initGameState(renderCall);
}

// Adds the given animation to the animation map.
void GameStateManager::addAnimToMap(std::string name, Animation* animation)
{
	animMap[name] = animation;
}

// Updates this GameState's GameWorld.
void GameStateManager::update()
{
	gameUpdateTimer->update();
	// - Only update every 60 frames
	if (gameUpdateTimer->ticks()) {
		this->updateGameWorld();
		// If a character is dead, go to the main screen.
		if (getCurrState()->getWorld() != nullptr) {
			/*for (int i = 0; i < getCurrState()->getWorld()->getCharacters().size(); i++) {
				if (getCurrState()->getWorld()->getCharacters()[i]->getLives() <= 0) {
					//setWelcomeState(getCurrState()->getWorld());
					//setWelcomeState();
					this->switchState(Welcome);
					std::cout << getCurrState()->getWorld()->getCharacters().size() << std::endl;
					// Reset their lives and health.
					for (int i = 0; i < getCurrState()->getWorld()->getCharacters().size(); i++) {
						getCurrState()->getWorld()->getCharacters()[i]->setLives(3);
						getCurrState()->getWorld()->getCharacters()[i]->setHealth(100);
					}
				}
			}*/
			for (auto c : getCurrState()->getWorld()->getCharacters()) {
				if (c->getLives() <= 0) {
					//setWelcomeState(getCurrState()->getWorld());
					//setWelcomeState();

					/*this->switchState(Welcome);
					std::cout << getCurrState()->getWorld()->getCharacters().size() << std::endl;
					// Reset their lives and health.

					for (auto c : getCurrState()->getWorld()->getCharacters()) {
						c->setLives(3);
						c->setHealth(100);
					}*/
					exit(0);
				}
			}
		}
	}
}


void GameStateManager::initWalkingAnim()
{
	Animation* char0moveLeft = new Animation(renderer,
		manager->getTexture("char_sprite_text0"),
		manager->getShader("char_sprite"),
		glm::vec2(0.142, 0.5),
		glm::vec2(0.142, 0.5),
		7, (double)1 / 25,
		glm::vec3(1, 1, 1)
	);

	Animation* char0moveRight = new Animation(renderer,
		manager->getTexture("char_sprite_text0"),
		manager->getShader("char_sprite"),
		glm::vec2(0.142, 0.5),
		glm::vec2(0.142, 0),
		7,
		(double)1 / 25
	);


	this->addAnimToMap("char0moveLeft", char0moveLeft);
	this->addAnimToMap("char0moveRight", char0moveRight);

	char0moveLeft->setScalingFactor(glm::vec2(0.05f, 0.125f));
	char0moveRight->setScalingFactor(glm::vec2(0.05f, 0.125f));


	Animation* char1moveLeft = new Animation(renderer,
		manager->getTexture("char_sprite_text1"),
		manager->getShader("char_sprite"),
		glm::vec2(0.142, 0.5),
		glm::vec2(0.142, 0.5),
		7, (double)1 / 25,
		glm::vec3(1, 1, 1));

	Animation* char1moveRight = new Animation(renderer,
		manager->getTexture("char_sprite_text1"),
		manager->getShader("char_sprite"),
		glm::vec2(0.142, 0.5),
		glm::vec2(0.142, 0),
		7, (double)1 / 25);


	this->addAnimToMap("char1moveLeft", char1moveLeft);
	this->addAnimToMap("char1moveRight", char1moveRight);

	char1moveLeft->setScalingFactor(glm::vec2(0.05f, 0.125f));
	char1moveRight->setScalingFactor(glm::vec2(0.05f, 0.125f));

}

void GameStateManager::initHatSprite()
{
}

// Update the GameState's GameWorld.
void GameStateManager::updateGameWorld()
{
	if (getCurrState()->getWorld() != nullptr) {
		this->getCurrState()->getWorld()->update();
	}
}