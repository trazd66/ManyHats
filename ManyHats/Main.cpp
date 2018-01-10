// Std. Includes
#include <iostream>
#include <map>
#include <string>

#include <glad/glad.h> 
// GLFW
#include <GLFW/glfw3.h>

#include "GL_Manager.h"
#include "GL_Sprite_Renderer.h"
// Properties
const GLuint WIDTH = 800, HEIGHT = 600;

GL_Manager* manager = new GL_Manager();
GL_Sprite_Renderer * renderer = new GL_Sprite_Renderer(WIDTH,HEIGHT);

// The MAIN function, from here we start our application and run the Game loop
int main()
{
	// Init GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr); // Windowed
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);

	// Set OpenGL options
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
		renderer->renderText(manager->GetShader("text_shader"), "This is sample text",glm::vec2( 25.0f, 25.0f), glm::vec3(0.5, 0.8f, 0.2f));
		// Swap the buffers
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}
