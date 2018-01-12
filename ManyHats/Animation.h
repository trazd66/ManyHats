#pragma once

#include "GL_Sprite_Renderer.h"

#include <iostream>
#include <vector>
using std::vector;


class Animation
{
public:
	Animation(GL_Sprite_Renderer * renderer, vector<Texture2D> textures, InGameObj* obj);
	~Animation();

	void start();// run the animaion

	void stop();// stop the animation
private:
	InGameObj* obj; // the in game object to animate

	Shader shader; //the shader that will be used in the rendering process of an animation

	vector<Texture2D> textures; //different texutres may be used in the rendering process of an animation
	//textures must be in the order of the animation

	Texture2D currTexture; // texture used currently

	GL_Sprite_Renderer * renderer; // pointer to a renderer that is initialized already.

	bool isRunning = false; // if the animation is running
};

