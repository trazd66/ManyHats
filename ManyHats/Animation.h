#pragma once

#include "GL_Sprite_Renderer.h"

#include <iostream>
#include <vector>
#include "Timer.h"
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
		int numToRender,
		double refreshRate,
		glm::vec3 colorOffSet = glm::vec3(1,1,1));

	~Animation();

	void render(InGameObj* obj);

	void updateCurrState();

	void staticRender(InGameObj* obj,int staticState);//used to render a non-moving object

	void setScalingFactor(glm::vec2 sFactor);

private:
	glm::vec3 colorOffSet;

	double xScaleFactor;
	double yScaleFactor;

	Timer *RefreshTimer;
	
	int currState;
	
	glm::vec2 spriteOffSet0;
	glm::vec2 spriteOffSet1;
	
	int renderCount;

	Shader shader; //the shader that will be used in the rendering process of an animation

	Texture2D currTexture; // texture used currently

	GL_Sprite_Renderer * renderer; // pointer to a renderer that is initialized already.

};

