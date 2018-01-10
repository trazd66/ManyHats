#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GL_Manager.h"
#include "GL_Sprite_Renderer.h"
#include "GameStateManager.h"
#include "GameWorld.h"

#define BACKGROUND_IMAGE "background.jpg"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);


// settings
GL_Manager * manager = new GL_Manager();
GL_Sprite_Renderer * renderer = new GL_Sprite_Renderer(manager);

GameStateManager* gsm = new GameStateManager();
GameWorld* game = new GameWorld();


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;



int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	// build and compile our shader program
	// ------------------------------------
	renderer->init();

	// Initiate the game.
	game->initiate();

	// TODO:  We probably can get rid of the BG_Shader?
	// manager->LoadShader("GLSL/BG_texture.vs", "GLSL/BG_texture.fs", nullptr, "BG_Shader");

	manager->LoadShader("GLSL/Char_texture.vs", "GLSL/Char_texture.fs", nullptr, "Char_Shader");
	manager->LoadTexture(BACKGROUND_IMAGE, false, "BG_Texture");

	char fileName1[game->getCharacters()[0]->getImage().size() + 1];
	int i;
	for (i = 0; i < game->getCharacters()[0]->getImage().size(); i++) {
		fileName1[i] = game->getCharacters()[0]->getImage()[i];
	}
	fileName1[i] = '\0';

	manager->LoadTexture(fileName1, true, "Char_Texture0");


	char fileName2[game->getCharacters()[1]->getImage().size() + 1];

	for (i = 0; i < game->getCharacters()[1]->getImage().size(); i++) {
		fileName2[i] = game->getCharacters()[1]->getImage()[i];
	}
	fileName2[i] = '\0';

	manager->LoadTexture(fileName2, true, "Char_Texture1");


	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Process keystrokes.
		gsm->processInput(game, window);

		// Update the game's state.
		game->update();

		// Rendering the background.
		renderer->renderSprite(
			manager->GetTexture("BG_Texture"),
			manager->GetShader("Char_Shader"),
			glm::vec2(400, 300));

		// Rendering the character.
		for (int i = 0; i < game->getCharacters().size(); i++) {
			renderer->renderSprite(
				manager->GetTexture("Char_Texture" + std::to_string(i)),
				manager->GetShader("Char_Shader"),
				glm::vec2(
					(float) (game->getCharacters()[i]->getLocation()[0]),
					(float) (game->getCharacters()[i]->getLocation()[1])),
				0.1f);
		}

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, renderer->getVAO());

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}