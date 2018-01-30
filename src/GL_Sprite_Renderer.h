#pragma once
// Game objects
#include "Character.h"
#include "Platform.h"

// GLM
#include "GL_Manager.h"

// IO
#include <iostream>
#include <map>


class GL_Sprite_Renderer
{
public:

	// Default constructor.
	GL_Sprite_Renderer(int SCREEN_WIDTH, int SCREEN_HEIGHT) : WIDTH(SCREEN_WIDTH), HEIGHT(SCREEN_HEIGHT)
	{};

	// Initiate the renderer.
	void initBufferBinding();

	// Render a given sprite, using the texture and shader given. 
	void renderSprite(Texture2D texture, Shader shader, glm::vec2 position, float scalingFactorX = 1.0f, float scalingFactorY = 1.0f);

	// Render a given animation.
	void renderAnim(
		Texture2D texture, 
		Shader shader, 
		glm::vec2 position, 
		glm::vec2 texOffSet0, 
		glm::vec2 texOffSet1, 
		float scalingFactorX = 1.0f, 
		float scalingFactorY = 1.0f, 
		glm::vec3 colorOffSet = glm::vec3(1,1,1)
	);

	// Render the given text, using a glyph.
	void renderText(Shader shader, std::string text, glm::vec2 position, glm::vec3 color, float scalingFactor = 1.0f);

	// Initialize the text rendering.
	void initTextRendering(Shader shader, std::map<char, Char>* characters);

	// Get the default VAO of this renderer.
	unsigned int* getVAO() {
		return &quadVAO;
	}

private:
	// The default VAO used by this renderer.
	unsigned int quadVAO;
	
	// The VAO, VBO binding for texts.
	unsigned int textVAO, textVBO;

	// Reference to the map of pre-loaded characters.
	std::map<char, Char> * characters;

	// Loads in the characters.
	void loadCharacters(std::map<char, Char>* characters);

	// The width and height of the screen.
	const int WIDTH, HEIGHT;
};

