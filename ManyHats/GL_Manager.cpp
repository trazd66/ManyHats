#include "GL_Manager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


Shader GL_Manager::LoadShader(const GLchar * vShaderFile, const GLchar * fShaderFile, const GLchar * gShaderFile, std::string name)
{
	Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
	return Shaders[name];
}

Shader GL_Manager::GetShader(std::string name)
{
	return Shaders[name];
}

Texture2D GL_Manager::LoadTexture(const GLchar * file, GLboolean alpha, std::string name)
{
	Textures[name] = loadTextureFromFile(file, alpha);
	return Textures[name];
}

Texture2D GL_Manager::GetTexture(std::string name)
{
	return Textures[name];
}

void GL_Manager::Clear()
{
	    // (Properly) delete all shaders	
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.getID());
    // (Properly) delete all textures
    for (auto iter : Textures)
        glDeleteTextures(1, iter.second.getTextureID());
}

Shader GL_Manager::loadShaderFromFile(const GLchar * vShaderFile, const GLchar * fShaderFile, const GLchar * gShaderFile)
{
	// 1. Retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	try
	{
		// Open files
		std::ifstream vertexShaderFile(vShaderFile);
		std::ifstream fragmentShaderFile(fShaderFile);
		std::stringstream vShaderStream, fShaderStream;
		// Read file's buffer contents into streams
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();
		// close file handlers
		vertexShaderFile.close();
		fragmentShaderFile.close();
		// Convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		// If geometry shader path is present, also load a geometry shader
		if (gShaderFile != nullptr)
		{
			std::ifstream geometryShaderFile(gShaderFile);
			std::stringstream gShaderStream;
			gShaderStream << geometryShaderFile.rdbuf();
			geometryShaderFile.close();
			geometryCode = gShaderStream.str();
		}
	}
	catch (std::exception e)
	{
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}
	const GLchar *vShaderCode = vertexCode.c_str();
	const GLchar *fShaderCode = fragmentCode.c_str();
	const GLchar *gShaderCode = geometryCode.c_str();//does nothing currently
	// 2. Now create shader object from source code

	Shader shader;
	shader.compile(vShaderCode, fShaderCode, gShaderCode);
	return shader;
}

Texture2D GL_Manager::loadTextureFromFile(const GLchar * file, GLboolean alpha)
{
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
	Texture2D texture; 
	texture.init(data, width, height, alpha);
	stbi_image_free(data);
	return texture;
}
