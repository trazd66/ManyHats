#pragma once
#include "Character.h"
#include "Platform.h"
#include"GL_Manager.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class GL_Sprite_Renderer
{
public:
	GL_Sprite_Renderer(GL_Manager* manager);
	~GL_Sprite_Renderer();

	void init();
	void renderSprite(Texture2D texture, Shader shader, glm::vec2 position, float scalingFactorX = 1.0f, float scalingFactorY = 1.0f);

	void draw(Character charToDraw);
	void draw(Platform platformToDraw);
	unsigned int* getVAO() {
		return &quadVAO;
	}
private:

	unsigned int quadVAO;

	GL_Manager* manager;

	void setManager(GL_Manager* theManager) {
		manager = theManager;
	}
};

