#include "Animation.h"


Animation::Animation(GL_Sprite_Renderer * renderer,
	Texture2D texture,
	Shader shader,
	glm::vec2 spriteOffSet0,
	glm::vec2 spriteOffSet1,
	int numToRender) :
	//initializing assets
	currTexture(texture),
	shader(shader),
	renderer(renderer),
	spriteOffSet0(spriteOffSet0),
	spriteOffSet1(spriteOffSet1),
	renderCount(numToRender)
{
}

Animation::~Animation()
{
}

void Animation::render(InGameObj* obj)
{
	nowTime = glfwGetTime();
	deltaTime += (nowTime - lastTime) / limitFPS;
	lastTime = nowTime;

	for (int i = 0; i < renderCount; i++) {
		// - Measure time
		renderer->renderAnim(
			currTexture,
			shader,
			glm::vec2(
			(float)(obj->getLocation()[0]),
				(float)(obj->getLocation()[1])),
			spriteOffSet0,
			glm::vec2((float)spriteOffSet1.x * i, spriteOffSet1.y),
			0.1f,
			0.25f);
	}
}
