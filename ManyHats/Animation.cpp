#include "Animation.h"






Animation::Animation(GL_Sprite_Renderer * renderer, vector<Texture2D> textures, InGameObj * obj)
{
	this->renderer = renderer;
	this->textures = textures;
	this->obj = obj;
}

Animation::~Animation()
{
}

void Animation::start()
{
	isRunning = true;
	glfwGetTime();
}

void Animation::stop()
{
	if (isRunning) {
		isRunning = false;
		


	}
}
