#include "Animation.h"

Animation::Animation(GL_Sprite_Renderer * renderer,
	Texture2D texture,
	Shader shader,
	glm::vec2 spriteOffSet0,
	glm::vec2 spriteOffSet1,
	int numToRender,
	double refreshRate,
	glm::vec3 colorOffSet) :

	//initializing assets
	currTexture(texture),
	shader(shader),
	renderer(renderer),
	spriteOffSet0(spriteOffSet0),
	spriteOffSet1(spriteOffSet1),
	renderCount(numToRender),
	colorOffSet(colorOffSet)
{
	RefreshTimer = new Timer(refreshRate);
}

Animation::~Animation()
{
}

void Animation::render(InGameObj* obj)
{
	RefreshTimer->update();
	if (this->RefreshTimer->ticks()) {
		this->updateCurrState();
	}
		renderer->renderAnim(
			currTexture,
			shader,
			glm::vec2(
			(float)(obj->getLocation()[0]),
				(float)(obj->getLocation()[1])),
			spriteOffSet0,
			glm::vec2((float)spriteOffSet1.x * currState, spriteOffSet1.y),
			xScaleFactor,
			yScaleFactor,
			colorOffSet);
}

void Animation::updateCurrState()
{
	if (currState < renderCount) {
		currState++;
	}
	else {
		currState = 0;
	}
}

void Animation::staticRender(InGameObj* obj,int staticState)
{
	renderer->renderAnim(
		currTexture,
		shader,
		glm::vec2(
		(float)(obj->getLocation()[0]),
		(float)(obj->getLocation()[1])),
		spriteOffSet0,
		glm::vec2((float)spriteOffSet1.x * staticState, spriteOffSet1.y),
		xScaleFactor,
		yScaleFactor,
		colorOffSet);
}

void Animation::setScalingFactor(glm::vec2 sFactor)
{
	this->xScaleFactor = sFactor.x;
	this->yScaleFactor = sFactor.y;
}
