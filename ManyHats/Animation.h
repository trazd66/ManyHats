#pragma once

#include "GL_Sprite_Renderer.h"

#include <iostream>
#include <vector>
using std::vector;


class Animation
{
public:
	Animation(
		GL_Sprite_Renderer * renderer,
		Texture2D texture,
		Shader shader, 
		glm::vec2 spriteOffSet0, 
		glm::vec2 spriteOffSet1, 
		int numToRender);

	~Animation();

	void render(InGameObj* obj);

private:
	double limitFPS = 1.0 / 5.0;

	double lastTime = glfwGetTime(), timer = lastTime;
	double deltaTime = 0, nowTime = 0;
	int frames = 0, updates = 0;

	float initX_vel;


	glm::vec2 spriteOffSet0;
	glm::vec2 spriteOffSet1;
	int renderCount;
	Shader shader; //the shader that will be used in the rendering process of an animation

	Texture2D currTexture; // texture used currently

	GL_Sprite_Renderer * renderer; // pointer to a renderer that is initialized already.

};

