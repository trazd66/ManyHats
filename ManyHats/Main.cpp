// Std. Includes
#include <iostream>
#include <map>
#include <string>

#include <glad/glad.h> 
// GLFW
#include <GLFW/glfw3.h>

#include "GL_Manager.h"
#include "GL_Sprite_Renderer.h"

#include "GameStateManager.h"
#include "GameWorld.h"

#define BACKGROUND_IMAGE "background.jpg"


// settings

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

GL_Manager * manager = new GL_Manager();
GL_Sprite_Renderer * renderer = new GL_Sprite_Renderer(SCR_WIDTH, SCR_HEIGHT);


GameWorld* game = new GameWorld();




// The MAIN function, from here we start our application and run the Game loop
int main()
{
	// Init GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


#ifdef __APPLE__
	// uncomment this statement to fix compilation on OS X
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	// build and compile our shader program
	// ------------------------------------
	renderer->initShader();

	// Initiate the game.
	game->initiate();

	// TODO:  We probably can get rid of the BG_Shader?
	// manager->LoadShader("GLSL/BG_texture.vs", "GLSL/BG_texture.fs", nullptr, "BG_Shader");

	manager->LoadShader("GLSL/Char_texture.vs", "GLSL/Char_texture.fs", nullptr, "Char_Shader");
	manager->LoadTexture(BACKGROUND_IMAGE, false, "BG_Texture");
	manager->loadFont("Fonts/AmaticSC-Regular.ttf");
	manager->LoadShader("GLSL/text_shader.vs", "GLSL/text_shader.fs", nullptr, "text_shader");

	renderer->initTextRendering(manager->GetShader("text_shader"), manager->getCharacterMap());
	// Compile and setup the shader
	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Check and call events
		glfwPollEvents();
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Rendering the background.
		renderer->renderSprite(
			manager->GetTexture("BG_Texture"),
			manager->GetShader("Char_Shader"),
			glm::vec2(400, 300));

		renderer->renderText(manager->GetShader("text_shader"),
			"Justin is god, shimi is dumb, im the bumbest",
			glm::vec2( 25.0f, 25.0f),
			glm::vec3(1, 0.0f, 0.0f));
		// Swap the buffers

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
