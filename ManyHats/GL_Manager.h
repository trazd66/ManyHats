#pragma once
#include "Shader.h"
#include "Texture2D.h"

#include <iostream>
#include <map>
#include <string>


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
	
	// Properly de-allocates all loaded resources
	void      Clear();
private:
	// Resource storage
	std::map<std::string, Shader>    Shaders;
	std::map<std::string, Texture2D> Textures;

	// Loads and generates a shader from file
	Shader    loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);
	// Loads a single texture from file
	Texture2D loadTextureFromFile(const GLchar *file, GLboolean alpha);
};

