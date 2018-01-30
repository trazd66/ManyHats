// Std. Includes
#include <iostream>
#include <map>
#include <string>

#include <glad/glad.h>

// GLFW
#include <GLFW/glfw3.h>

#include "GL_Manager.h"
#include "GL_Sprite_Renderer.h"
#include "InputManager.h"
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

#include "GameStateManager.h"

#define BACKGROUND_IMAGE "src/Sprites/background.png"



// Make a GL_Manager, GL_Sprite_Renderer and GameStateManager for the game.
GL_Manager * manager = new GL_Manager();
GL_Sprite_Renderer * renderer = new GL_Sprite_Renderer(SCR_WIDTH, SCR_HEIGHT);
GameStateManager* gsm = new GameStateManager(manager, renderer);

// The MAIN function, from here we start our application and run the Game loop
int main()
{
	// Initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "THGDL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return 1;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);


	// build and compile our shader program
	// ------------------------------------
	renderer->initBufferBinding();
	manager->LoadShader("src/GLSL/text_shader.vs", "src/GLSL/text_shader.fs", nullptr, "Text_Shader");
	manager->loadFont("src/Fonts/Vera.ttf");
	renderer->initTextRendering(manager->getShader("Text_Shader"), manager->getCharacterMap());


	manager->LoadShader("src/GLSL/Char_texture.vs", "src/GLSL/Char_texture.fs", nullptr, "Char_Shader");
	manager->LoadTexture(BACKGROUND_IMAGE, false, "BG_Texture");
	manager->LoadTexture("src/Sprites/hatshop.png",false,"init_BG_Texture");

	manager->LoadTexture("src/platform.jpg", false, "Platform_Texture");
	manager->LoadTexture("src/Sprites/start.png", true, "Button_Texture");

	manager->LoadTexture("src/Sprites/walkingSprite0.png", true, "char_sprite_text0");
	manager->LoadTexture("src/Sprites/walkingSprite1.png", true, "char_sprite_text1");
	manager->LoadShader("src/GLSL/sprite_sheat.vs", "src/GLSL/sprite_sheat.fs", nullptr, "char_sprite");

	manager->LoadTexture("src/Sprites/head0.png", true, "head0");
	manager->LoadTexture("src/Sprites/head1.png", true, "head1");

	manager->LoadTexture("src/Sprites/hats.png",true,"hats");

	gsm->init();
	InputManager::setCursorCallBack(window);
	InputManager::loadCurrGameState(gsm->getCurrState());

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// Check and call events.
		glfwPollEvents();
		if (gsm->getCurrState()->getWorld() != nullptr) {

			InputManager::process_DUO_gameplay_input(gsm, window);

			// Update the game's state, if the game is not meant to be paused.
			if (!gsm->getPaused()) {
				gsm->update();
				gsm->unpauseGame();
			}
			else {
				gsm->pauseGame();
			}
		}
		gsm->getCurrState()->renderCall();


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
	}


	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, renderer->getVAO());

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}
