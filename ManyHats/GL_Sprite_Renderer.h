#pragma once
//game objects
#include "Character.h"
#include "Platform.h"

//glm

#include "GL_Manager.h"

//IO
#include <iostream>
#include <map>


class GL_Sprite_Renderer
{
public:
	GL_Sprite_Renderer(int SCREEN_WIDTH, int SCREEN_HEIGHT):WIDTH(SCREEN_WIDTH),HEIGHT(SCREEN_HEIGHT){};
	//initiate the renderer
	void initShader();

<<<<<<< HEAD
	void init();
	void renderSprite(Texture2D texture, Shader shader, glm::vec2 position, float scalingFactorX = 1.0f, float scalingFactorY = 1.0f);
=======
	// render a given sprite, using the texture and shader given 
	void renderSprite(Texture2D texture, Shader shader, glm::vec2 position, float scalingFactor = 1.0f);
	
	//render a given sprite, using a glyph
	void renderText(Shader shader, std::string text, glm::vec2 position, glm::vec3 color, float scalingFactor = 1.0f);
>>>>>>> 99001905878edc048aa2abce4290f652038b19af

	void initTextRendering(Shader shader, std::map<char, Char> * characters);

	//get the default VAO of this renderer
	unsigned int* getVAO() {
		return &quadVAO;
	}

private:
	//the default VAO used by this renderer
	unsigned int quadVAO;
	
	//the VAO, VBO binding for texts
	unsigned int textVAO, textVBO;

	// reference to the map of pre-loaded characters
	std::map<char, Char> * characters;

	void loadCharacters(std::map<char, Char>* characters);

	const int WIDTH, HEIGHT;
};

