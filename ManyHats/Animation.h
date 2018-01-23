#pragma once

#include "GL_Sprite_Renderer.h"

#include <iostream>
#include <vector>
using std::vector;

// Allows for the characters to be animated.
class Animation
{
public:

	// Default constructor.
	Animation(
		GL_Sprite_Renderer * renderer,
		Texture2D texture,
		Shader shader, 
		glm::vec2 spriteOffSet0, 
		glm::vec2 spriteOffSet1, 
		int numToRender
	);

	// Default destructor.
	~Animation();

	// Renders the animated object.
	void render(InGameObj* obj);

private:

	// The FPS limit.
	double limitFPS = 1.0 / 5.0;

	// The last time that was recorded.
	double lastTime = glfwGetTime(), timer = lastTime;

	// The difference between the last time and the current time.
	double deltaTime = 0, nowTime = 0;

	int frames = 0, updates = 0;

	// The initial x-velocity of the object being animated.
	float initX_vel;


	glm::vec2 spriteOffSet0;
	glm::vec2 spriteOffSet1;
	int renderCount;
	Shader shader; //the shader that will be used in the rendering process of an animation

	Texture2D currTexture; // texture used currently

	GL_Sprite_Renderer * renderer; // pointer to a renderer that is initialized already.

};

