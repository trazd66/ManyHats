#include "Animation.h"

// Default constructor.
Animation::Animation(GL_Sprite_Renderer * renderer,
	Texture2D texture,
	Shader shader,
	glm::vec2 spriteOffSet0,
	glm::vec2 spriteOffSet1,
	int numToRender
) : 
	// Initializing assets.
	currTexture(texture),
	shader(shader),
	renderer(renderer),
	spriteOffSet0(spriteOffSet0),
	spriteOffSet1(spriteOffSet1),
	renderCount(numToRender)
{
}

// Default destructor.
Animation::~Animation()
{
}

// Renders the animated object.
void Animation::render(InGameObj* obj)
{
	// Gets the time in between now and the last time this was called.
	nowTime = glfwGetTime();
	deltaTime += (nowTime - lastTime) / limitFPS;
	lastTime = nowTime;

	for (int i = 0; i < renderCount; i++) {
		// - Measure time

		// Renders the current 
		renderer->renderAnim(
			currTexture,
			shader,
			glm::vec2(
				(float)(obj->getLocation()[0]),
				(float)(obj->getLocation()[1])),
				spriteOffSet0,
				glm::vec2((float)spriteOffSet1.x * i, spriteOffSet1.y),
			0.1f,
			0.25f
		);
	}
}
