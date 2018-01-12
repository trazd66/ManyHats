#pragma once

//openGL helper
#include "Shader.h"
#include "Texture2D.h"

//IO
#include <iostream>
#include <map>
#include <string>


//text rendering
#include <ft2build.h>
#include FT_FREETYPE_H


struct Char {
	GLuint TextureID;   // ID handle of the glyph texture
	glm::ivec2 Size;    // Size of glyph
	glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
	GLuint Advance;    // Horizontal offset to advance to next glyph
};


class GL_Manager
{
public:
	GL_Manager(){};
	// Loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
	Shader   LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name);
	
	// Retrieves a stored sader
	Shader   GetShader(std::string name);
	
	// Loads (and generates) a texture from file
	Texture2D LoadTexture(const GLchar *file, GLboolean alpha, std::string name);
	
	// Retrieves a stored texture
	Texture2D GetTexture(std::string name);
	
	//load a font, and store it in Characters
	void loadFont(const GLchar * fontPath);

	// Properly de-allocates all loaded resources
	void Clear();

	std::map<char, Char> * getCharacterMap() {
		return & characters;
	}

private:
	// Resource storage
	std::map<std::string, Shader>    Shaders;
	std::map<std::string, Texture2D> Textures;

	// the map of pre-loaded characters
	std::map<char, Char> characters;


	// Loads and generates a shader from file
	Shader    loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);
	// Loads a single texture from file
	Texture2D loadTextureFromFile(const GLchar *file, GLboolean alpha);
};

