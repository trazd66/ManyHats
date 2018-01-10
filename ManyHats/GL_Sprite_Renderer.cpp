#include "GL_Sprite_Renderer.h"


void GL_Sprite_Renderer::initShader()
{
	unsigned int VBO, EBO;
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// positions          // colors           // texture coords
		1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-1.0f, -1.0f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-1.0f,  1.0f, 0.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
	};

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	//VAO: Stores bindings and enables for vertex attributes as well as the binding for the index list.
	//Does not store any data (content) within the bound arrays/buffers,
	//but "does" (different from what you said) store references to the arrays/buffers.
	//So strictly speaking the arrays/buffers must be created first (so you have the addresses and/or buffer handles to put in the VAO).
	glGenVertexArrays(1, &quadVAO);

	//VBO: Can contain a list of numbers, but even more generally, a buffer object is just a list of bytes.
	// You tell the GPU how to pull data out of this buffer (offsets, data types, interleaving, etc.).
	//The order of binding VBOs and VAOs "is" relevant, as binding VBOs changes the bound VAO.
	glGenBuffers(1, &VBO);

	//EBOs: These are just buffer objects used differently. So see VBO: above for everything you need to know.
	//The only reason there's a distinction is that you bind these buffer objects to a different bind point
	// so the GPU pulls DrawElements index data from it rather than vertex attributes
	glGenBuffers(1, &EBO);


	//-----------------------------------------------
	glBindVertexArray(quadVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

	//color attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

	// texture coord attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

}

void GL_Sprite_Renderer::loadCharacters(std::map<char, Char>* characters)
{
	this->characters = characters;
}


void GL_Sprite_Renderer::renderSprite(Texture2D texture, Shader shader, glm::vec2 position, float scalingFactor)
{


	// bind textures on corresponding texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *texture.getTextureID());   // TextureID of Char is 3.

																						 // create transformations
	//glm::mat4 transform = glm::ortho(0.0f, static_cast<GLfloat>(WIDTH), 0.0f, static_cast<GLfloat>(HEIGHT));

	// create transformations
	glm::mat4 transform;

	// Changes position from a vector (x, y) with 0 <= x <= 800, 0 <= y <= 600
	// to a vector (x', y') with -1 <= x', y' <= 1 (which is the form that OpenGL needs).
	position[0] *= 1.0f / (WIDTH/2);
	position[1] *= 1.0f / (HEIGHT/2);
	position -= glm::vec2(1.0f, 1.0f);

	transform = glm::translate(transform, glm::vec3(position, 0.0f));

	//transform the size of the
	transform = glm::scale(transform, glm::vec3(scalingFactor, scalingFactor, scalingFactor));

	// The following line rotates the character.  I am keeping it here in case we need to use it in the future.
	// transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

	// render container
	shader.use();
	// get matrix's uniform location and set matrix
	unsigned int ID = shader.getID();
	int transformLoc = glGetUniformLocation(ID, "transform");
	// Check for errors.
	if (transformLoc < 0) {
		perror("glGetUniformLocation");
		exit(1);
	}

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
	glBindVertexArray(quadVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}



void GL_Sprite_Renderer::renderText(Shader shader, std::string text, glm::vec2 position, glm::vec3 color, float scalingFactor)
{
	// Activate corresponding render state	
	shader.use();
	shader.SetVector3f("textColor", color, false);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(textVAO);

	// Iterate through all characters
	std::string::const_iterator c;
	std::map<char, Char> charMap = *characters;
	for (c = text.begin(); c != text.end(); c++)
	{
		Char ch = charMap[*c];
		GLfloat xpos = position.x + ch.Bearing.x * scalingFactor;
		GLfloat ypos = position.y - (ch.Size.y - ch.Bearing.y) * scalingFactor;

		GLfloat w = ch.Size.x * scalingFactor;
		GLfloat h = ch.Size.y * scalingFactor;
		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, textVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		position.x += (ch.Advance >> 6) * scalingFactor; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void GL_Sprite_Renderer::initTextRendering(Shader shader, std::map<char, Char> * characters)
{
	this->loadCharacters(characters);
	glGenVertexArrays(1, &this->textVAO);
	glGenBuffers(1, &textVBO);
	glBindVertexArray(this->textVAO);
	glBindBuffer(GL_ARRAY_BUFFER, textVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Compile and setup the shader
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(WIDTH), 0.0f, static_cast<GLfloat>(HEIGHT));
	shader.use();
	shader.SetMatrix4("projection", projection, false);

}





